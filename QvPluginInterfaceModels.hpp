#pragma once

#include <QMap>
#include <QObject>

namespace Qv2rayPlugin
{
    Q_NAMESPACE

    enum OutboundInfoFlags
    {
        INFO_PROTOCOL = 0,
        INFO_SERVER = 1,
        INFO_PORT = 2,
        INFO_SNI = 3
    };

    enum KernelOptionFlags
    {
        KERNEL_HTTP_ENABLED,
        KERNEL_HTTP_PORT,
        KERNEL_SOCKS_ENABLED,
        KERNEL_SOCKS_PORT,
        KERNEL_SOCKS_UDP_ENABLED,
        KERNEL_SOCKS_LOCAL_ADDRESS,
        KERNEL_LISTEN_ADDRESS
    };

    namespace Events
    {
        namespace SystemProxy
        {
            enum SystemProxyStateType
            {
                SetProxy,
                ClearProxy
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
                      systemProxyState(type){};
            };
        } // namespace SystemProxy

        namespace ConnectionStats
        {
            struct EventObject
            {
                QString displayName;
                long upLinkSpeed;
                long downLinkSpeed;
                quint64 upLinkData;
                quint64 downLinkData;
            };
        } // namespace ConnectionStats

        namespace Connectivity
        {
            enum EventType
            {
                Connecting,
                Connected,
                Disconnecting,
                Disconnected
            };
            struct EventObject
            {
                EventType eventType;
                QString displayName;
                QMap<QString, int> inboundPorts;
                EventObject(){};
                EventObject(const QString &name, const QMap<QString, int> &ports, const EventType &event)
                    : eventType(event), displayName(name), inboundPorts(ports){};
            };
        } // namespace Connectivity

        namespace ConnectionEntry
        {
            enum EventType
            {
                Created,
                Edited,
                Renamed,
                LinkedWithGroup,
                RemovedFromGroup,
                FullyRemoved
            };
            struct EventObject
            {
                EventType eventType;
                QString displayName;
                QString originalDisplayName;
            };
        } // namespace ConnectionEntry
    }     // namespace Events

} // namespace Qv2rayPlugin
