#pragma once
#include <QObject>
namespace Qv2rayPlugin
{
    Q_NAMESPACE
    //
    //
    //
    enum QvSystemProxyType
    {
        SystemProxy_HTTP,
        SystemProxy_SOCKS
    };
    struct QvSystemProxyEventObject
    {
        QString displayName;
        QvSystemProxyType systemProxyType;
        uint systemProxyPort;
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
        QvConnectivityEventType eventType;
    };
    //
    //
    //
    enum QvItemEventType
    {
        ConnectionEvent_Created,
        ConnectionEvent_Renamed,
        ConnectionEvent_Updated,
        ConnectionEvent_Deleted
    };
    struct QvItemEventObject
    {
        QString displayName;
        QString originalDisplayName;
        QvItemEventType eventType;
    };
    //
    //
    //
    enum QV2RAY_PLUGIN_UI_TYPE
    {
        /// The UI in the Outbound Editor
        UI_TYPE_OUTBOUND_EDITOR,
        /// The UI in the Inbound Editor
        UI_TYPE_INBOUND_EDITOR,
        /// The UI in the Group Editor
        UI_TYPE_GROUP_EDITOR
    };
    Q_ENUM_NS(QV2RAY_PLUGIN_UI_TYPE)
    //
    enum QV2RAY_PLUGIN_PROCESSTYPE
    {
        PROCESSTYPE_NONE,
        /// This plugin listens on group (Creation, Renaming, Modifying, Updating (subscription) and Removing)
        /// and connection               (Creation, Renaming, Modifying, Latency Testing and Removing)
        PROCESSTYPE_ITEM,
        /// This plugin listens on connection Pre-Connect, Post-Connection, Pre-Disconnect and Post-Disconnect
        PROCESSTYPE_CONNECTIVITY,
        /// This plugin listens on statistics event
        PROCESSTYPE_STATS,
        /// This plugin listens on system proxy settings.
        PROCESSTYPE_SYSTEMPROXY
    };
    Q_ENUM_NS(QV2RAY_PLUGIN_PROCESSTYPE)
    //
    enum QV2RAY_SPECIAL_PLUGIN_TYPE
    {
        /// This plugin is a connection kernel, providing new types of outbound.
        SPECIAL_TYPE_KERNEL,
        /// This plugin provides manual serialization of a connection,
        SPECIAL_TYPE_SERIALIZOR,
        /// No special things.
        SPECIAL_TYPE_NONE
    };
    Q_ENUM_NS(QV2RAY_SPECIAL_PLUGIN_TYPE)
    //
    //
    //
    typedef QList<QV2RAY_PLUGIN_PROCESSTYPE> QV2RAY_PLUGIN_PROCESSTYPE_FLAGS;
    typedef QList<QV2RAY_SPECIAL_PLUGIN_TYPE> QV2RAY_SPECIAL_PLUGIN_TYPE_FLAGS;

} // namespace Qv2rayPlugin
