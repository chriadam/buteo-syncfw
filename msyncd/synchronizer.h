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
#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include "SyncDBusInterface.h"
#include "SyncQueue.h"
#include "StorageBooker.h"
#include "SyncScheduler.h"
#include "SyncBackup.h"

#include "SyncCommonDefs.h"
#include "ProfileManager.h"
#include "PluginManager.h"
#include "PluginCbInterface.h"
#include "ClientPlugin.h"

#include <QVector>
#include <QMutex>
#include <QCoreApplication>
#include <QMap>
#include <QString>
#include <QDBusInterface>


class ContextProperty;

namespace Buteo {

class PluginManager;
class ServerPluginRunner;
class TransportTracker;
class ServerActivator;
class AccountsHelper;

/// \brief The main entry point to the synchronization framework.
///
/// This class manages other components and connects them to provide
/// the fully functioning synchronization framework.
class Synchronizer : public SyncDBusInterface, // Derived from QObject
		     public PluginCbInterface
{
    Q_OBJECT
public:

    /// \brief The contructor.
    Synchronizer(QCoreApplication *aApplication);

    /// \brief Destructor
    virtual ~Synchronizer();

    /// \brief registers the dbus service and creates handlers for various
    /// tasks of the synchronizer
    bool initialize();

    /// \brief stops the daemon and unregisters the dbus object
    void close();


// From PluginCbInterface
// ---------------------------------------------------------------------------
    /// \see PluginCbInterface::requestStorage
    virtual bool requestStorage(const QString &aStorageName,
                                const SyncPluginBase *aCaller);

    /// \see PluginCbInterface::releaseStorage
    virtual void releaseStorage(const QString &aStorageName,
                                const SyncPluginBase *aCaller);

    /// \see PluginCbInterface::createStorage
    virtual StoragePlugin* createStorage(const QString &aPluginName);

    /// \see PluginCbInterface::destroyStorage
    virtual void destroyStorage(StoragePlugin *aStorage);

    /// \see PluginCbInterface::isConnectivityAvailable
    virtual bool isConnectivityAvailable( Sync::ConnectivityType aType );


// From SyncDBusInterface
// --------------------------------------------------------------------------

public slots:

    //! \see SyncDBusInterface::startSync
    virtual bool startSync(QString aProfileName);

    //! \see SyncDBusInterface::abortSync
    virtual void abortSync(QString aProfileName);

    //! \see SyncDBusInterface::addProfile
    virtual bool addProfile(QString aProfileAsXml);

    //! \see SyncDBusInterface::removeProfile
    virtual bool removeProfile(QString aProfileAsXml);

    //! \see SyncDBusInterface::updateProfile
    virtual bool updateProfile(QString aProfileAsXml);

    //! \see SyncDBusInterface::requestStorages
    virtual bool requestStorages(QStringList aStorageNames);

    //! \see SyncDBusInterface::releaseStorages
    virtual void releaseStorages(QStringList aStorageNames);

    //! \see SyncDBusInterface::runningSyncs
    virtual QStringList runningSyncs();

    //! \see SyncDBusInterface::setSyncSchedule
    virtual bool setSyncSchedule(QString aProfileId , QString aScheduleAsXml);

    //! \see SyncDBusInterface::saveSyncResults
    virtual bool saveSyncResults(QString aProfileId,QString aSyncResults);

    /*! \brief To get lastSyncResult.
     *  \param aProfileId
     *  \return QString of syncResult.
     */
    virtual QString getLastSyncResult(const QString &aProfileId);
// --------------------------------------------------------------------------

    //! Called  starts a schedule sync.
    bool startScheduledSync(QString aProfileName);

    //! Called  when backup starts
    void backupStarts();

    //! Called when backup is completed
    void backupFinished();

    //! Called when  starting to restore a backup.
    void restoreStarts();

    //! Called when backup is restored
    void restoreFinished();

    //! Called to get the current backup/restore state
    virtual bool getBackUpRestoreState();

    //! handles any changes in the accounts profile
    virtual void handleAccountsProfileChange(QString,int);

signals:

	//! emitted by releaseStorages call
    void storageReleased();

private slots:

    /*! \brief Handler for storage released signal.
     *
     * Tries to start the next sync in queue, which may have been blocked
     * earlier by storage reservations.
     */
    void onStorageReleased();

    void onTransferProgress( const QString &aProfileName,
        Sync::TransferDatabase aDatabase, Sync::TransferType aType,
        const QString &aMimeType, int aCommittedItems );

    void onSessionFinished( const QString &aProfileName,
        Sync::SyncStatus aStatus, const QString &aMessage, int aErrorCode );

    void onStorageAccquired(const QString &aProfileName, const QString &aMimeType);
    
    void onSyncProgressDetail(const QString &aProfileName,int aProgressDetail);

    void onServerDone();

    void onNewSession(const QString &aDestination);

    /*! \brief Starts a server plug-in
     *
     * @param aProfileName Server profile name
     */
    void startServer(const QString &aProfileName);

    /*! \brief Stops a server plug-in
     *
     * @param aProfileName Server profile name
     */
    void stopServer(const QString &aProfileName);

private:

    bool startSync(const QString &aProfileName, bool aScheduled);

    /*! \brief Starts a sync with the given profile.
     *
     * \param aProfile Profile to use in sync. Ownership is transferred.
     *  The profile is automatically deleted when the sync finishes.
     */
    bool startSyncNow(SyncSession *aSession);

    /*! \brief Tries to starts next sync request from the sync queue.
     *
     * \return Is it possible to try starting more syncs by calling this
     *  function again. Will be true if the first sync request in the queue
     *  is not blocked by already reserved storages.
     */
    bool startNextSync();

    void cleanupSession(SyncSession *aSession);

    /*! \brief Start all server plug-ins
     *
     * @param resume, if true resume servers instead of starting them
     */
    void startServers( bool resume = false );

    /*! \brief Stop all server plug-ins
     *
     * @param suspend, if true suspend servers instead of stopping them
     */
    void stopServers( bool suspend = false );

    /*! \brief Helper function when backup/restore starts.
     *
     */
     void backupRestoreStarts ();
	    
    /*! \brief Helper function when backup/restore is done.
     *
     */
     void backupRestoreFinished();
    
    /*! \brief Adds a profile to sync scheduler
     *
     * @param aProfileName Name of the profile to schedule.
     */
    void reschedule(const QString &aProfileName);

    /*! \brief Initializes sync scheduler
     *
     */
    void initializeScheduler();

    bool isBackupRestoreInProgress ();
    
    QMap<QString, SyncSession*> iActiveSessions;

    QMap<QString, ServerPluginRunner*> iServers;

    PluginManager iPluginManager;

    ProfileManager iProfileManager;

    SyncQueue iSyncQueue;

    StorageBooker iStorageBooker;

    SyncScheduler *iSyncScheduler;
    
    SyncBackup *iSyncBackup;

    TransportTracker *iTransportTracker;

    ServerActivator *iServerActivator;

    AccountsHelper *iAccounts;

    ContextProperty *iLowPower;

    bool iClosing;

#ifdef SYNCFW_UNIT_TESTS
    friend class SynchronizerTest;
#endif

    QDBusInterface *iSyncUIInterface;
};

}

#endif // SYNCHRONIZER_H