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
        virtual void SetHostAddress(const QString &address, int port) = 0;
        virtual QPair<QString, int> GetHostAddress() const = 0;
        //
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject GetContent() const = 0;

      protected:
        QJsonObject content;
    };

#define AddEditor(type, protocol, displayName, editorType)                                                                                      \
    this->type##Editors.append({ ProtocolInfoObject{ protocol, displayName }, std::make_unique<editorType>() })

    class PluginGUIInterface
    {
      public:
        using typed_plugin_editor = QPair<ProtocolInfoObject, std::shared_ptr<QvPluginEditor>>;
        explicit PluginGUIInterface(){};
        virtual ~PluginGUIInterface(){};
        virtual QIcon Icon() const = 0;
        virtual QList<PluginGuiComponentType> GetComponents() const = 0;
        virtual std::shared_ptr<QvPluginSettingsWidget> GetSettingsWidget() const final
        {
            return settingsWidget;
        }
        virtual QList<typed_plugin_editor> GetInboundEditors() const final
        {
            return inboundEditors;
        }
        virtual QList<typed_plugin_editor> GetOutboundEditors() const final
        {
            return outboundEditors;
        }
        virtual std::shared_ptr<QvPluginMainWindowWidget> GetMainWindowWidget() const final
        {
            return mainWindowWidget;
        }

      protected:
        std::shared_ptr<QvPluginSettingsWidget> settingsWidget;
        QList<typed_plugin_editor> inboundEditors;
        QList<typed_plugin_editor> outboundEditors;
        std::shared_ptr<QvPluginMainWindowWidget> mainWindowWidget;
    };

} // namespace Qv2rayPlugin
