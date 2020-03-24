#pragma once

#include <QFlags>
#include <QIcon>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QWidget>

constexpr auto QV2RAY_PLUGIN_INTERFACE_VERSION = 1;

namespace Qv2ray
{
    Q_NAMESPACE
    enum QV2RAY_PLUGIN_HOOK_TYPE
    {
        HOOK_TYPE_NONE,
        /// This plugin listens on group (Creation, Renaming, Modifying, Updating (subscription) and Removing)
        /// and connection               (Creation, Renaming, Modifying, Latency Testing and Removing)
        HOOK_TYPE_CONFIG_EVENTS,
        /// This plugin listens on connection Pre-Connect, Post-Connection, Pre-Disconnect and Post-Disconnect
        HOOK_TYPE_CONFIG_STATE_EVENTS,
        /// This plugin listens on statistics event
        HOOK_TYPE_STATS_EVENTS
    };

    enum QV2RAY_PLUGIN_HOOK_SUBTYPE
    {
        HOOK_STYPE_CREATED,
        HOOK_STYPE_RENAMED,
        HOOK_STYPE_MODIFIED,
        HOOK_STYPE_UPDATED,
        HOOK_STYPE_REMOVED,
        //
        HOOK_STYPE_LATENCY_UPDATED,
        HOOK_STYPE_PRE_CONNECTING,
        HOOK_STYPE_POST_CONNECTED,
        HOOK_STYPE_PRE_DISCONNECTING,
        HOOK_STYPE_POST_DISCONNECTED,
        //
        HOOK_STYPE_STATS_CHANGED
    };

    enum QV2RAY_SPECIAL_PLUGIN_TYPE
    {
        /// This plugin is a connection kernel, providing new types of outbound.
        SPECIAL_TYPE_KERNEL,
        /// This plugin provides manual serialization of a connection,
        SPECIAL_TYPE_SERIALIZATION,
        /// This plugin provides manual final config generation,
        SPECIAL_TYPE_GENERATION,
        /// No special things.
        SPECIAL_TYPE_NONE
    };

    enum QV2RAY_PLUGIN_UI_TYPE
    {
        /// The UI in the Preference Window
        UI_TYPE_PREFERENCE_WINDOW,
        /// The UI in the Outbound Editor
        UI_TYPE_OUTBOUND_EDITOR,
        /// The UI in the Inbound Editor
        UI_TYPE_INBOUND_EDITOR,
        /// The UI in the Group Editor
        UI_TYPE_GROUP_EDITOR
    };

    Q_ENUM_NS(QV2RAY_PLUGIN_UI_TYPE)
    Q_ENUM_NS(QV2RAY_PLUGIN_HOOK_TYPE)
    Q_ENUM_NS(QV2RAY_PLUGIN_HOOK_SUBTYPE)
    Q_ENUM_NS(QV2RAY_SPECIAL_PLUGIN_TYPE)

    Q_DECLARE_FLAGS(QV2RAY_PLUGIN_HOOK_TYPE_FLAGS, QV2RAY_PLUGIN_HOOK_TYPE)

    class Qv2rayKernelPlugin : public QObject
    {
        Q_OBJECT
        // Events handlers
        /// Kernel related operations
        virtual bool StartKernel(const QJsonObject) = 0;
        virtual bool StopKernel() = 0;

      signals:
        /// Kernel related operations
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvaliable(const QString &);
    };

    class Qv2rayInterface
    {
      public:
        const int QvPluginInterfaceVersion = QV2RAY_PLUGIN_INTERFACE_VERSION;
        //
        virtual ~Qv2rayInterface() = default;
        //
        virtual QV2RAY_PLUGIN_HOOK_TYPE_FLAGS PluginHooks() const = 0;
        virtual QV2RAY_SPECIAL_PLUGIN_TYPE SpecialPluginType() const = 0;
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
        virtual QWidget *GetUIWidgets(QV2RAY_PLUGIN_UI_TYPE) = 0;
        /// If the plugin is a kernel,
        virtual Qv2rayKernelPlugin *GetKernelInstance() = 0;
        virtual QObject *GetQObject() = 0;
        //
        virtual void InitializePlugin(const QJsonObject &) = 0;
        virtual const QJsonObject GetPluginSettngs() = 0;
        //
        /// The hook function, for SPECIAL_TYPE_NONE
        virtual void PluginHook(QV2RAY_PLUGIN_HOOK_TYPE, QV2RAY_PLUGIN_HOOK_SUBTYPE, QVariant) = 0;
        // TODO:
        // Kernel type handling
        // Serializaiton handling
        // Geneation handling
        virtual void PluginLog(const QString &) const = 0;
    };
} // namespace Qv2ray

QT_BEGIN_NAMESPACE
#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"
Q_DECLARE_INTERFACE(Qv2ray::Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
