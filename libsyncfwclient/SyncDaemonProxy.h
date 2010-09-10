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
 * Command line was: qdbusxml2cpp -p SyncDaemonProxy -N -c SyncDaemonProxy com.meego.msyncd.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef SYNCDAEMONPROXY_H_1280213538
#define SYNCDAEMONPROXY_H_1280213538

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*! \brief Proxy class for interface com.meego.msyncd
 */
class SyncDaemonProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    //! \brief  returns Interface Name
    static inline const char *staticInterfaceName()
    { return "com.meego.msyncd"; }

public:
    //! \see SyncDBusInterface::SyncDBusInterface()
    SyncDaemonProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    //! \see SyncDBusInterface::SyncDBusInterface()
    ~SyncDaemonProxy();

public Q_SLOTS: // METHODS

    //! \see SyncDBusInterface::abortSync()
    inline Q_NOREPLY void abortSync(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        callWithArgumentList(QDBus::NoBlock, QLatin1String("abortSync"), argumentList);
    }

    //! \see SyncDBusInterface::addProfile()
    inline QDBusPendingReply<bool> addProfile(const QString &aProfileAsXml)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileAsXml);
        return asyncCallWithArgumentList(QLatin1String("addProfile"), argumentList);
    }

    //! \see SyncDBusInterface::getBackUpRestoreState()
    inline QDBusPendingReply<bool> getBackUpRestoreState()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("getBackUpRestoreState"), argumentList);
    }

    //! \see SyncDBusInterface::getLastSyncResult()
    inline QDBusPendingReply<QString> getLastSyncResult(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("getLastSyncResult"), argumentList);
    }

    //! \see SyncDBusInterface::isLastSyncScheduled()
    inline QDBusPendingReply<bool> isLastSyncScheduled(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("isLastSyncScheduled"), argumentList);
    }

    //! \see SyncDBusInterface::lastSyncMajorCode()
    inline QDBusPendingReply<int> lastSyncMajorCode(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("lastSyncMajorCode"), argumentList);
    }

    //! \see SyncDBusInterface::lastSyncMinorCode()
    inline QDBusPendingReply<int> lastSyncMinorCode(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("lastSyncMinorCode"), argumentList);
    }
    //! \see SyncDBusInterface::lastSyncTime()
    inline QDBusPendingReply<QString> lastSyncTime(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("lastSyncTime"), argumentList);
    }

    //! \see SyncDBusInterface::releaseStorages()
    inline Q_NOREPLY void releaseStorages(const QStringList &aStorageNames)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aStorageNames);
        callWithArgumentList(QDBus::NoBlock, QLatin1String("releaseStorages"), argumentList);
    }

    //! \see SyncDBusInterface::removeProfile()
    inline QDBusPendingReply<bool> removeProfile(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("removeProfile"), argumentList);
    }

    //! \see SyncDBusInterface::requestStorages()
    inline QDBusPendingReply<bool> requestStorages(const QStringList &aStorageNames)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aStorageNames);
        return asyncCallWithArgumentList(QLatin1String("requestStorages"), argumentList);
    }

    //! \see SyncDBusInterface::runningSyncs()
    inline QDBusPendingReply<QStringList> runningSyncs()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("runningSyncs"), argumentList);
    }

    //! \see SyncDBusInterface::saveSyncResults()
    inline QDBusPendingReply<bool> saveSyncResults(const QString &aProfileId, const QString &aSyncResults)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId) << qVariantFromValue(aSyncResults);
        return asyncCallWithArgumentList(QLatin1String("saveSyncResults"), argumentList);
    }

    //! \see SyncDBusInterface::setSyncSchedule()
    inline QDBusPendingReply<bool> setSyncSchedule(const QString &aProfileId, const QString &aScheduleAsXml)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId) << qVariantFromValue(aScheduleAsXml);
        return asyncCallWithArgumentList(QLatin1String("setSyncSchedule"), argumentList);
    }

    //! \see SyncDBusInterface::startSync()
    inline QDBusPendingReply<bool> startSync(const QString &aProfileId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileId);
        return asyncCallWithArgumentList(QLatin1String("startSync"), argumentList);
    }

    //! \see SyncDBusInterface::updateProfile()
    inline QDBusPendingReply<bool> updateProfile(const QString &aProfileAsXml)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(aProfileAsXml);
        return asyncCallWithArgumentList(QLatin1String("updateProfile"), argumentList);
    }

Q_SIGNALS: // SIGNALS

    //! \see SyncDBusInterface::backupDone()
    void backupDone();

    //! \see SyncDBusInterface::backupInProgress()
    void backupInProgress();

    //! \see SyncDBusInterface::restoreDone()
    void restoreDone();

    //! \see SyncDBusInterface::restoreInProgress()
    void restoreInProgress();

    //! \see SyncDBusInterface::resultsAvailable()
    void resultsAvailable(const QString &aProfileName, const QString &aResultsAsXml);

    //! \see SyncDBusInterface::signalProfileChanged()
    void signalProfileChanged(const QString &aProfileName, int aChangeType, const QString &aProfileAsXml);

    //! \see SyncDBusInterface::syncStatus()
    void syncStatus(const QString &aProfileName, int aStatus, const QString &aMessage, int aErrorCode);

    //! \see SyncDBusInterface::transferProgress()
    void transferProgress(const QString &aProfileName, int aTransferDatabase, int aTransferType, const QString &aMimeType, int aCommittedItems);
};

#endif