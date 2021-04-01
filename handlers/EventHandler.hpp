#pragma once
#include <QMap>

namespace Qv2rayPlugin::handlers::event
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

    namespace _details
    {
        template<typename... T>
        class Qp
        {
          public:
            void ProcessEvent(){};
        };

        template<typename T1, typename... T2>
        class Qp<T1, T2...> : public Qp<T2...>
        {
          public:
            using Qp<T2...>::ProcessEvent;
            virtual void ProcessEvent(const T1 &pluginEvent){ Q_UNUSED(pluginEvent) };
        };
    } // namespace _details

    class PluginEventHandler
        : public _details::Qp<Connectivity::EventObject, SystemProxy::EventObject, ConnectionEntry::EventObject, ConnectionStats::EventObject>
    {
    };
} // namespace Qv2rayPlugin::handlers::event

using namespace Qv2rayPlugin::handlers::event;
