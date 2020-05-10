#pragma once

#include "QvPluginProcessor.hpp"

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QWidget>
#include <memory>

constexpr auto QV2RAY_PLUGIN_INTERFACE_VERSION = 2;

namespace Qv2rayPlugin
{
    class Qv2rayInterface
    {
      public:
        const int QvPluginInterfaceVersion = QV2RAY_PLUGIN_INTERFACE_VERSION;
        //
        virtual ~Qv2rayInterface() = default;
        //
        /// Basic metainfo of this plugin
        virtual const QvPluginMetadata GetMetadata() const = 0;
        /// Initilise Plugin using plugin settings directory and a Json-contained plugin settings.
        virtual bool Initialize(const QString &, const QJsonObject &) = 0;
        /// Update Plugin Settings.
        virtual bool UpdateSettings(const QJsonObject &) = 0;
        /// Get Plugin Setting
        virtual const QJsonObject GetSettngs() = 0;
        /// \brief Get the settings widget of this plugin.
        /// \warning The owner of this widget is the caller.
        /// \returns A unique pointer to QWidget of settings widget, the widget will be deleted after use each time.
        virtual std::unique_ptr<QWidget> GetSettingsWidget() = 0;
        /// \brief Get editor widget of this plugin, if any, according to the UI_TYPE
        /// \arg UI_TYPE type of the desired ui
        /// \warning The owner of this widget is the caller, the widget will be deleted after use each time.
        /// \returns A unique pointer to the QvPluginEditor instance.
        virtual std::unique_ptr<QvPluginEditor> GetEditorWidget(UI_TYPE) = 0;
        /// \brief Get Kernel Instance if the QvPluginMetadata contains SPECIAL_TYPE_KERNEL
        /// \warning The owner of this QvPluginKernel instance is the plugin instance itself.
        virtual std::shared_ptr<QvPluginKernel> GetKernel() = 0;
        /// \brief Get Serializer Instance if the QvPluginMetadata contains SPECIAL_TYPE_SERIALIZOR
        /// \warning The owner of this QvPluginSerializer instance is the plugin instance itself.
        virtual std::shared_ptr<QvPluginSerializer> GetSerializer() = 0;
        /// \brief Get QvPluginEventHandler Instance. This should not return a nullptr
        /// \warning The owner of this QvPluginEventHandler instance is the plugin instance itself.
        virtual std::shared_ptr<QvPluginEventHandler> GetEventHandler() = 0;
        //
        /// \brief Signal to emit when a plugin need to write log messages.
        virtual void PluginLog(const QString &) const = 0;
        /// \brief Signal to emit when a plugin need to popup an error message box.
        virtual void PluginErrorMessageBox(const QString &) const = 0;
    };
} // namespace Qv2rayPlugin

QT_BEGIN_NAMESPACE
#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"
Q_DECLARE_INTERFACE(Qv2rayPlugin::Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
