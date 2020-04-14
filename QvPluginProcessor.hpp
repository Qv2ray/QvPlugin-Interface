#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QJsonObject>
#include <QObject>
#include <QtWidgets>

#define __QVPLUGIN_EVENT_HANDLER_SIG(type) const ::Qv2rayPlugin::Events::type::EventObject &pluginEvent
#define __QVPLUGIN_DECL_EVENT_HANDLER(type) void ProcessEvent_##type(__QVPLUGIN_EVENT_HANDLER_SIG(type))

#define QvPlugin_EventHandler_Decl(type) __QVPLUGIN_DECL_EVENT_HANDLER(type) override
#define QvPlugin_EventHandler(className, type) void className::ProcessEvent_##type(__QVPLUGIN_EVENT_HANDLER_SIG(type))

namespace Qv2rayPlugin
{
    class QvPluginSerializer : public QObject
    {
        Q_OBJECT
      public:
        explicit QvPluginSerializer(QObject *parent = nullptr) : QObject(parent){};
        virtual const QString SerializeOutbound(const QString &protocol,  //
                                                const QString &alias,     //
                                                const QString &groupName, //
                                                const QJsonObject &object) const = 0;
        virtual const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const = 0;
        virtual const QList<QString> ShareLinkPrefixes() const = 0;
        virtual const QList<QString> OutboundProtocols() const = 0;
    };

    class QvPluginEditor : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginEditor(QWidget *parent = nullptr) : QWidget(parent){};
        //
        virtual void SetHostInfo(const QString &address, int port) = 0;
        virtual QPair<QString, int> GetHostInfo() const = 0;
        //
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject GetContent() const = 0;
        //
        virtual void SwitchOutbound(const QString &) = 0;
        virtual QList<QvPluginOutboundObject> OutboundCapabilities() const = 0;
    };

    class QvPluginKernel : public QObject
    {
        Q_OBJECT
      public:
        explicit QvPluginKernel(QObject *parent = nullptr) : QObject(parent){};
        /// Kernel related operations
        virtual void SetConnectionSettings(const QString &listenAddress, const QMap<QString, int> &inbound, const QJsonObject &settings) = 0;
        virtual bool StartKernel() = 0;
        virtual bool StopKernel() = 0;
        virtual const QList<QvPluginOutboundObject> KernelOutboundCapabilities() const = 0;
        //
      signals:
        /// Kernel related operations
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvaliable(const QString &);
        void OnKernelStatsAvailable(quint64 upSpeed, quint64 downSpeed);
    };

    class QvPluginEventHandler : public QObject
    {
        Q_OBJECT
      public:
        explicit QvPluginEventHandler(QObject *parent = nullptr) : QObject(parent){};
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(ConnectionStats){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(SystemProxy){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(Connectivity){ Q_UNUSED(pluginEvent) };
        virtual __QVPLUGIN_DECL_EVENT_HANDLER(ConnectionEntry){ Q_UNUSED(pluginEvent) };
    };
} // namespace Qv2rayPlugin
