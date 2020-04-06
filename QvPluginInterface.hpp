#pragma once

#include "Qv2rayPluginObjects.hpp"
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
        virtual QV2RAY_PLUGIN_PROCESSTYPE_FLAGS PluginHooks() const = 0;
        virtual QV2RAY_SPECIAL_PLUGIN_TYPE_FLAGS SpecialPluginType() const = 0;
        //
        // Basic metainfo of this plugin
        /// Display name of this plugin
        virtual QString Name() const = 0;
        /// Internal name of this plugin
        virtual QString InternalName() const = 0;
        /// The author of this plugin
        virtual QString Author() const = 0;
        /// A brief description of the plugin
        virtual QString Description() const = 0;
        /// The icon of the plugin
        virtual const QIcon Icon() const = 0;
        //
        /// A list of valid outbounds where this plugin is capable to handle, if any.
        virtual QStringList OutboundTypes() const = 0;
        //
        /// The UI Widget object of the plugin.
        virtual Qv2rayPluginEditorWidget *GetEditorWidget(QV2RAY_PLUGIN_UI_TYPE) = 0;
        virtual QWidget *GetSettingsWidget() = 0;
        /// If the plugin is a kernel,
        virtual Qv2rayKernelPluginObject *GetKernelInstance() = 0;
        virtual QObject *GetQObject() = 0;
        virtual Qv2rayPluginProcessor *PluginProcessor() = 0;
        //
        virtual bool InitializePlugin(const QString &, const QJsonObject &) = 0;
        virtual bool UpdatePluginSettings(const QJsonObject &) = 0;
        virtual const QJsonObject GetPluginSettngs() = 0;
        //
        // TODO:
        // Kernel type handling
        // Serializaiton handling
        // Geneation handling
        virtual void PluginLog(const QString &) const = 0;
        virtual void PluginErrorMessageBox(const QString &) const = 0;
    };
} // namespace Qv2rayPlugin

QT_BEGIN_NAMESPACE
#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"
Q_DECLARE_INTERFACE(Qv2rayPlugin::Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
