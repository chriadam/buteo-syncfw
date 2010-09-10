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

/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -a SyncDBusAdaptor -c SyncDBusAdaptor com.meego.msyncd.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "SyncDBusAdaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class SyncDBusAdaptor
 */

SyncDBusAdaptor::SyncDBusAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

SyncDBusAdaptor::~SyncDBusAdaptor()
{
    // destructor
}

void SyncDBusAdaptor::abortSync(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.abortSync
    QMetaObject::invokeMethod(parent(), "abortSync", Q_ARG(QString, aProfileId));
}

bool SyncDBusAdaptor::addProfile(const QString &aProfileAsXml)
{
    // handle method call com.meego.msyncd.addProfile
    bool out0;
    QMetaObject::invokeMethod(parent(), "addProfile", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileAsXml));
    return out0;
}

bool SyncDBusAdaptor::getBackUpRestoreState()
{
    // handle method call com.meego.msyncd.getBackUpRestoreState
    bool out0;
    QMetaObject::invokeMethod(parent(), "getBackUpRestoreState", Q_RETURN_ARG(bool, out0));
    return out0;
}

QString SyncDBusAdaptor::getLastSyncResult(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.getLastSyncResult
    QString aSyncResultAsString;
    QMetaObject::invokeMethod(parent(), "getLastSyncResult", Q_RETURN_ARG(QString, aSyncResultAsString), Q_ARG(QString, aProfileId));
    return aSyncResultAsString;
}

bool SyncDBusAdaptor::isLastSyncScheduled(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.isLastSyncScheduled
    bool out0;
    QMetaObject::invokeMethod(parent(), "isLastSyncScheduled", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileId));
    return out0;
}

int SyncDBusAdaptor::lastSyncMajorCode(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.lastSyncMajorCode
    int aMajorCode;
    QMetaObject::invokeMethod(parent(), "lastSyncMajorCode", Q_RETURN_ARG(int, aMajorCode), Q_ARG(QString, aProfileId));
    return aMajorCode;
}

int SyncDBusAdaptor::lastSyncMinorCode(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.lastSyncMinorCode
    int aMinorCode;
    QMetaObject::invokeMethod(parent(), "lastSyncMinorCode", Q_RETURN_ARG(int, aMinorCode), Q_ARG(QString, aProfileId));
    return aMinorCode;
}

QString SyncDBusAdaptor::lastSyncTime(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.lastSyncTime
    QString aTimeAsString;
    QMetaObject::invokeMethod(parent(), "lastSyncTime", Q_RETURN_ARG(QString, aTimeAsString), Q_ARG(QString, aProfileId));
    return aTimeAsString;
}

void SyncDBusAdaptor::releaseStorages(const QStringList &aStorageNames)
{
    // handle method call com.meego.msyncd.releaseStorages
    QMetaObject::invokeMethod(parent(), "releaseStorages", Q_ARG(QStringList, aStorageNames));
}

bool SyncDBusAdaptor::removeProfile(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.removeProfile
    bool out0;
    QMetaObject::invokeMethod(parent(), "removeProfile", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileId));
    return out0;
}

bool SyncDBusAdaptor::requestStorages(const QStringList &aStorageNames)
{
    // handle method call com.meego.msyncd.requestStorages
    bool out0;
    QMetaObject::invokeMethod(parent(), "requestStorages", Q_RETURN_ARG(bool, out0), Q_ARG(QStringList, aStorageNames));
    return out0;
}

QStringList SyncDBusAdaptor::runningSyncs()
{
    // handle method call com.meego.msyncd.runningSyncs
    QStringList out0;
    QMetaObject::invokeMethod(parent(), "runningSyncs", Q_RETURN_ARG(QStringList, out0));
    return out0;
}

bool SyncDBusAdaptor::saveSyncResults(const QString &aProfileId, const QString &aSyncResults)
{
    // handle method call com.meego.msyncd.saveSyncResults
    bool out0;
    QMetaObject::invokeMethod(parent(), "saveSyncResults", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileId), Q_ARG(QString, aSyncResults));
    return out0;
}

bool SyncDBusAdaptor::setSyncSchedule(const QString &aProfileId, const QString &aScheduleAsXml)
{
    // handle method call com.meego.msyncd.setSyncSchedule
    bool out0;
    QMetaObject::invokeMethod(parent(), "setSyncSchedule", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileId), Q_ARG(QString, aScheduleAsXml));
    return out0;
}

bool SyncDBusAdaptor::startSync(const QString &aProfileId)
{
    // handle method call com.meego.msyncd.startSync
    bool out0;
    QMetaObject::invokeMethod(parent(), "startSync", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileId));
    return out0;
}

bool SyncDBusAdaptor::updateProfile(const QString &aProfileAsXml)
{
    // handle method call com.meego.msyncd.updateProfile
    bool out0;
    QMetaObject::invokeMethod(parent(), "updateProfile", Q_RETURN_ARG(bool, out0), Q_ARG(QString, aProfileAsXml));
    return out0;
}
