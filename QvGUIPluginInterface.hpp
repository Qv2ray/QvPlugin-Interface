#pragma once
#include "QvPluginBase.hpp"

#include <QMenu>
#include <QWidget>

namespace Qv2rayPlugin
{
    class QvPluginSettingsWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginSettingsWidget(QWidget *parent) : QWidget(parent){};
        virtual ~QvPluginSettingsWidget() = 0;
    };
    class QvPluginMainWindowWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginMainWindowWidget(QWidget *parent) : QWidget(parent){};
        virtual ~QvPluginMainWindowWidget() = 0;
        virtual const QList<QMenu *> GetMenus() = 0;
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
        virtual QList<OutboundInfoObject> OutboundCapabilities() const = 0;
    };

    class Qv2rayPluginGUIInterface
    {
      public:
        explicit Qv2rayPluginGUIInterface(){};
        virtual ~Qv2rayPluginGUIInterface() = 0;
        virtual QIcon Icon() const = 0;
        /// Qv2ray will take the ownership.
        virtual std::unique_ptr<QvPluginSettingsWidget> GetSettingsWidget() const = 0;
        /// Qv2ray will NOT take the ownership.
        virtual std::shared_ptr<QvPluginEditor> GetInboundEditor() const = 0;
        virtual std::shared_ptr<QvPluginEditor> GetOutboundEditor() const = 0;
        virtual std::shared_ptr<QvPluginMainWindowWidget> GetMainWindowWidget() const = 0;
    };

} // namespace Qv2rayPlugin
