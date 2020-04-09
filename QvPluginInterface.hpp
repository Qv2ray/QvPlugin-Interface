#pragma once

#include "Qv2rayPluginProcessor.hpp"

#include <QFlags>
#include <QIcon>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QWidget>

constexpr auto QV2RAY_PLUGIN_INTERFACE_VERSION = 1;

namespace Qv2rayPlugin
{
    class Qv2rayInterface
    {
      public:
        const int QvPluginInterfaceVersion = QV2RAY_PLUGIN_INTERFACE_VERSION;
        //
        virtual ~Qv2rayInterface() = default;
        //
        //
        // Basic metainfo of this plugin
        virtual const QvPluginMetadata GetMetadata() const = 0;
        //
        //
        //
        virtual bool Initialize(const QString &, const QJsonObject &) = 0;
        virtual bool UpdateSettings(const QJsonObject &) = 0;
        virtual const QJsonObject GetSettngs() = 0;
        //
        //
        virtual QWidget *GetSettingsWidget() = 0;
        virtual QvPluginEditor *GetEditorWidget(UI_TYPE) = 0;
        virtual QvPluginKernel *GetKernel() = 0;
        virtual QvPluginSerializer *GetSerializer() = 0;
        virtual QvPluginEventHandler *GetEventHandler() = 0;
        //
        //
        virtual void PluginLog(const QString &) const = 0;
        virtual void PluginErrorMessageBox(const QString &) const = 0;
    };
} // namespace Qv2rayPlugin

QT_BEGIN_NAMESPACE
#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"
Q_DECLARE_INTERFACE(Qv2rayPlugin::Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
