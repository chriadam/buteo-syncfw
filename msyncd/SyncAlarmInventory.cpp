/*
 * This file is part of buteo-syncfw package
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Sateesh Kavuri <sateesh.kavuri@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include "SyncAlarmInventory.h"

#include <QTimer>
#include <QObject>
#include <QSettings>
#include <QDebug>
#include <LogMacros.h>

const QString ALARM_CONNECTION_NAME( "alarms" );

// Use this to calculate the number of times a iTimer has to be triggered.
// For now, we just divide the next trigger time by 2 and use that value
const int TRIGGER_COUNT = 2;

SyncAlarmInventory::SyncAlarmInventory()
{
  // empty.explicitly call init
}

bool SyncAlarmInventory::init()
{
    static unsigned connectionNumber = 0;
    iConnectionName = ALARM_CONNECTION_NAME + QString::number( connectionNumber++ );
    iDbHandle = QSqlDatabase::addDatabase( "QSQLITE", iConnectionName );

    QString path( QDir::home().path() );
    path.append( QDir::separator() ).append( ".sync");
    path.append( QDir::separator() ).append( "alarms.db.sqlite" );
    path = QDir::toNativeSeparators( path );

    iDbHandle.setDatabaseName( path );

    if (!iDbHandle.open()) {
    	LOG_CRITICAL("Failed to OPEN DB. SCHEDULING WILL NOT WORK");
    	return false;
    } else {
    	LOG_DEBUG("DB Opened Successfully");
    }

    // Create the alarms table
    const QString createTableQuery( "CREATE TABLE IF NOT EXISTS alarms(alarmid INTEGER PRIMARY KEY AUTOINCREMENT, synctime DATETIME)" );
    QSqlQuery query( createTableQuery, iDbHandle );
    if ( !query.exec() ) {
    	LOG_WARNING("Failed to execute the createTableQuery");
    	return false;
    }

    // Create the iTimer object
    iTimer = new QTimer(this);
    if(iTimer) {
    	connect( iTimer, SIGNAL(timeout()), this, SLOT(timerTriggered()) );
    	currentAlarm = 0;
    	return true;
    } else {
    	LOG_WARNING("Failed to create a QTimer");
    	return false;
    }
}

SyncAlarmInventory::~SyncAlarmInventory()
{
    iDbHandle.close();
    iDbHandle = QSqlDatabase();
    QSqlDatabase::removeDatabase( iConnectionName );
    
    if (iTimer) {
        iTimer->stop();
        delete iTimer;
	    iTimer = 0;
    }
}

int SyncAlarmInventory::addAlarm( QDateTime alarmDate )
{
    // Check if alarmDate < QDateTime::currentDateTime()
    if ( QDateTime::currentDateTime().secsTo(alarmDate) < 0 ) {
    	return 0;
    	LOG_WARNING("alarmDate < QDateTime::currentDateTime()");
    }

    // Store the alarm 
    int alarmId = 0;
    if ( (alarmId = addAlarmToDb(alarmDate)) == 0 ) {
        // Note: Even incase of an already existing profile, false is returned by the query
        // There is no way to detect a record insertion from an already existing alarm

        // If unable to add an alarm to db, set the iTimers
        // for already existing alarms
    	LOG_WARNING("(alarmId = addAlarmToDb(alarmDate)) == 0");
    }

    // Select all the alarms from the db sorted by alarm time
    QSqlQuery selectQuery( iDbHandle );
    if ( selectQuery.exec("SELECT alarmid,synctime FROM alarms ORDER BY synctime ASC") ) {
        if ( selectQuery.first() ) {
            int newAlarm = selectQuery.value(0).toInt();
            QDateTime alarmTime = selectQuery.value(1).toDateTime();

            // If the newAlarm != currentAlarm that is fetched from DB, stop the
            // previous iTimer
            if ( (currentAlarm != 0) && (newAlarm != currentAlarm) ) {
                if ( !iTimer->isActive() )
                    iTimer->stop();
            }

            // This is a new alarm. Set the iTimer for the alarm
            currentAlarm = newAlarm;
            QDateTime now = QDateTime::currentDateTime();
            int iTimerInterval = (now.secsTo( alarmTime ) / TRIGGER_COUNT) * 1000;  // time interval in millisec
            triggerCount = TRIGGER_COUNT;
            iTimer->setInterval( iTimerInterval );
            iTimer->start();
        }
    } else {
    	LOG_WARNING("Select Query Execution Failed" );
    }

    return alarmId;
}

bool SyncAlarmInventory::removeAlarm(int alarmId)
{
    if( alarmId <= 0 ) return false;
    deleteAlarmFromDb( alarmId );
    return true;
}

void SyncAlarmInventory::timerTriggered()
{
    // Decrement the alarm counter
    triggerCount--;

    // Alarm expired. Trigger the alarm and delete it from DB and set the alarm for the next one
    if (triggerCount == 0) {
    	LOG_DEBUG("Triggering the alarm " << currentAlarm );
        emit triggerAlarm(currentAlarm);

        // Delete the alarm from DB
        if ( !deleteAlarmFromDb(currentAlarm) ) {
        }
        iTimer->stop();
        currentAlarm = 0;

        // Set the new alarm iTimer
        // Select all the alarms from the db sorted by alarm time
        QSqlQuery selectQuery( iDbHandle );
        if ( selectQuery.exec("SELECT alarmid,synctime FROM alarms ORDER BY synctime ASC") ) {
            if ( selectQuery.first() ) {
                currentAlarm = selectQuery.value(0).toInt();
                QDateTime alarmTime = selectQuery.value(1).toDateTime();

                // Set the iTimer for the alarm
                QDateTime now = QDateTime::currentDateTime();
                int iTimerInterval = (now.secsTo( alarmTime ) / TRIGGER_COUNT) * 1000;  // time interval in millisec
                triggerCount = TRIGGER_COUNT;
                iTimer->setInterval( iTimerInterval );
                iTimer->start();
            }
        }
    }
}

bool SyncAlarmInventory::deleteAlarmFromDb( int alarmId )
{
    QSqlQuery removeQuery ( iDbHandle );
    removeQuery.prepare( "DELETE FROM alarms WHERE alarmid=:alarmid" );
    removeQuery.bindValue( ":alarmid", alarmId );

    if ( !removeQuery.exec() )
        return false;
    else
        return true;
}

int SyncAlarmInventory::addAlarmToDb( QDateTime timeStamp )
{
    QSqlQuery insertQuery( iDbHandle );
    insertQuery.prepare( "INSERT INTO alarms(synctime) VALUES(:synctime)" );
    insertQuery.bindValue( ":synctime", timeStamp );

    if ( insertQuery.exec() )
        return insertQuery.lastInsertId().toInt();
    else
        return 0;
}