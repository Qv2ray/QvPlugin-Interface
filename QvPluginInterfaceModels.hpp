#pragma once
#include <QMap>
#include <QObject>
namespace Qv2rayPlugin
{
    Q_NAMESPACE
    //
    //
    //
    enum QvSystemProxyStateType
    {
        SystemProxyState_SetProxy,
        SystemProxyState_ClearProxy
    };
    enum QvSystemProxyType
    {
        SystemProxy_HTTP,
        SystemProxy_SOCKS
    };
    struct QvSystemProxyEventObject
    {
        QString displayName;
        QMap<QvSystemProxyType, int> systemProxyPortSettings;
        QvSystemProxyStateType systemProxyState;
    };
    //
    //
    //
    /// Struct holding information for connection stats events.
    struct QvConnectionStatsEventObject
    {
        QString displayName;
        quint64 upLinkSpeed;
        quint64 downLinkSpeed;
        int64_t upLinkData;
        int64_t downLinkData;
    };
    //
    //
    //
    enum QvConnectivityEventType
    {
        QvConnecticity_Connecting,
        QvConnecticity_Connected,
        QvConnecticity_Disconnecting,
        QvConnecticity_Disconnected
    };
    struct QvConnectivityEventObject
    {
        QString displayName;
        QMap<QString, int> inboundPorts;
        QvConnectivityEventType eventType;
        QvConnectivityEventObject()
        {
        }
        QvConnectivityEventObject(const QString &name, const QMap<QString, int> &ports, const QvConnectivityEventType &event)
            : displayName(name),   //
              inboundPorts(ports), //
              eventType(event)     //
        {
        }
    };
    //
    //
    //
    enum QvConnectionEntryEventType
    {
        ConnectionEvent_Created,
        ConnectionEvent_Renamed,
        ConnectionEvent_Updated,
        ConnectionEvent_Deleted
    };
    struct QvConnectionEntryEventObject
    {
        QString displayName;
        QString originalDisplayName;
        QvConnectionEntryEventType eventType;
    };
    //
    //
    //
    enum UI_TYPE
    {
        /// The UI in the Outbound Editor
        UI_TYPE_OUTBOUND_EDITOR,
        /// The UI in the Inbound Editor
        UI_TYPE_INBOUND_EDITOR,
        /// The UI in the Group Editor
        UI_TYPE_GROUP_EDITOR
    };
    Q_ENUM_NS(UI_TYPE)
    //
    enum CAPABILITY
    {
        CAPABILITY_NONE,
        /// This plugin listens on group (Creation, Renaming, Modifying, Updating (subscription) and Removing)
        /// and connection               (Creation, Renaming, Modifying, Latency Testing and Removing)
        CAPABILITY_CONNECTION_ENTRY,
        /// This plugin listens on connection Pre-Connect, Post-Connection, Pre-Disconnect and Post-Disconnect
        CAPABILITY_CONNECTIVITY,
        /// This plugin listens on statistics event
        CAPABILITY_STATS,
        /// This plugin listens on system proxy settings.
        CAPABILITY_SYSTEM_PROXY
    };
    Q_ENUM_NS(CAPABILITY)
    typedef QList<CAPABILITY> CAPABILITY_FLAGS;
    //
    //
    //
    enum SPECIAL_TYPE
    {
        /// This plugin is a connection kernel, providing new types of outbound.
        SPECIAL_TYPE_KERNEL,
        /// This plugin provides manual serialization of a connection,
        SPECIAL_TYPE_SERIALIZOR,
        /// No special things.
        SPECIAL_TYPE_NONE
    };
    Q_ENUM_NS(SPECIAL_TYPE)
    typedef QList<SPECIAL_TYPE> SPECIAL_TYPE_FLAGS;
} // namespace Qv2rayPlugin
