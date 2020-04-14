#pragma once
#include <QIcon>
#include <QMap>
#include <QObject>
namespace Qv2rayPlugin
{
    Q_NAMESPACE
    struct QvPluginOutboundObject
    {
        QString displayName;
        QString protocol;
    };
    namespace Events
    {

        namespace SystemProxy
        {
            enum SystemProxyStateType
            {
                SystemProxyState_SetProxy,
                SystemProxyState_ClearProxy
            };
            enum SystemProxyType
            {
                SystemProxy_HTTP,
                SystemProxy_SOCKS
            };
            struct EventObject
            {
                QMap<SystemProxyType, int> systemProxyPortSettings;
                SystemProxyStateType systemProxyState;
                EventObject(){};
                EventObject(const QMap<SystemProxyType, int> &port, const SystemProxyStateType &type)
                    : systemProxyPortSettings(port), //
                      systemProxyState(type)         //
                {
                }
            };
        } // namespace SystemProxy
        namespace ConnectionStats
        {
            struct EventObject
            {
                QString displayName;
                quint64 upLinkSpeed;
                quint64 downLinkSpeed;
                int64_t upLinkData;
                int64_t downLinkData;
            };
        } // namespace ConnectionStats
        namespace Connectivity
        {
            enum EventType
            {
                QvConnecticity_Connecting,
                QvConnecticity_Connected,
                QvConnecticity_Disconnecting,
                QvConnecticity_Disconnected
            };
            struct EventObject
            {
                QString displayName;
                QMap<QString, int> inboundPorts;
                EventType eventType;
                EventObject()
                {
                }
                EventObject(const QString &name, const QMap<QString, int> &ports, const EventType &event)
                    : displayName(name),   //
                      inboundPorts(ports), //
                      eventType(event)     //
                      {};
            };
        } // namespace Connectivity

        namespace ConnectionEntry
        {
            enum EventType
            {
                ConnectionEvent_Created,
                ConnectionEvent_Renamed,
                ConnectionEvent_Updated,
                ConnectionEvent_Deleted
            };
            struct EventObject
            {
                QString displayName;
                QString originalDisplayName;
                EventType eventType;
            };
        } // namespace ConnectionEntry
    }     // namespace Events
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

    enum SPECIAL_TYPE
    {
        /// This plugin is a connection kernel, providing new types of outbound.
        SPECIAL_TYPE_KERNEL,
        /// This plugin provides manual serialization of a connection,
        SPECIAL_TYPE_SERIALIZOR
    };
    Q_ENUM_NS(SPECIAL_TYPE)
    typedef QList<SPECIAL_TYPE> SPECIAL_TYPE_FLAGS;

    struct QvPluginMetadata
    {
        QString Name;
        QString Author;
        QString InternalName;
        QString Description;
        QIcon Icon;
        //
        CAPABILITY_FLAGS Capabilities;
        SPECIAL_TYPE_FLAGS SpecialPluginType;
        QvPluginMetadata(const QString &name,                    //
                         const QString &author,                  //
                         const QString &internalName,            //
                         const QString &description,             //
                         const QIcon &icon,                      //
                         const CAPABILITY_FLAGS &caps,           //
                         const SPECIAL_TYPE_FLAGS &specialTypes) //
            : Name(name),                                        //
              Author(author),                                    //
              InternalName(internalName),                        //
              Description(description),                          //
              Icon(icon),                                        //
              Capabilities(caps),                                //
              SpecialPluginType(specialTypes)
        {
        }
        QvPluginMetadata(){};
    };
} // namespace Qv2rayPlugin
