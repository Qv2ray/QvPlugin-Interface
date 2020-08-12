#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QJsonObject>
#include <QObject>

#define __QVPLUGIN_EVENT_HANDLER_SIG(type) const ::Qv2rayPlugin::Events::type::EventObject &pluginEvent
#define __QVPLUGIN_DECL_EVENT_HANDLER(type) void ProcessEvent_##type(__QVPLUGIN_EVENT_HANDLER_SIG(type))

#define QvPlugin_EventHandler_Decl(type) __QVPLUGIN_DECL_EVENT_HANDLER(type) override
#define QvPlugin_EventHandler(className, type) void className::ProcessEvent_##type(__QVPLUGIN_EVENT_HANDLER_SIG(type))

namespace Qv2rayPlugin
{
    class PluginOutboundHandler : public QObject
    {
        Q_OBJECT
      public:
        explicit PluginOutboundHandler(QObject *parent = nullptr) : QObject(parent){};
        virtual const QString SerializeOutbound(const QString &protocol,  //
                                                const QString &alias,     //
                                                const QString &groupName, //
                                                const QJsonObject &object) const = 0;
        virtual const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const = 0;
        virtual const OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const = 0;
        virtual const QMap<QString, QString> SupportedProtocols() const = 0;
    };

    class PluginKernel : public QObject
    {
        Q_OBJECT
      public:
        explicit PluginKernel(QObject *parent = nullptr) : QObject(parent){};
        virtual ~PluginKernel(){};
        virtual void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const QJsonObject &connectionInfo) = 0;
        virtual bool StartKernel() = 0;
        virtual bool StopKernel() = 0;
        //
      signals:
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvailable(const QString &);
        void OnKernelStatsAvailable(quint64 upSpeed, quint64 downSpeed);

      private:
        QString __qvKernelId;
    };

    class PluginEventHandler : public QObject
    {
        Q_OBJECT
      public:
        explicit PluginEventHandler(QObject *parent = nullptr) : QObject(parent){};
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(ConnectionStats){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(SystemProxy){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(Connectivity){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(ConnectionEntry){ Q_UNUSED(pluginEvent) };
    };
} // namespace Qv2rayPlugin
