#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QJsonObject>
#include <QObject>
#include <QtWidgets>

#define QVPlUGIN_DECL_EVENT_HANDLER(type) virtual void ProcessEvent_##type(const ::Qv2rayPlugin::Qv##type##EventObject &)
#define QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(type) QVPlUGIN_DECL_EVENT_HANDLER(type) override

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
        /// Key = DisplayName, Value = protocol.
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
        QVPlUGIN_DECL_EVENT_HANDLER(ConnectionStats){};
        QVPlUGIN_DECL_EVENT_HANDLER(SystemProxy){};
        QVPlUGIN_DECL_EVENT_HANDLER(Connectivity){};
        QVPlUGIN_DECL_EVENT_HANDLER(ConnectionEntry){};
    };
} // namespace Qv2rayPlugin
