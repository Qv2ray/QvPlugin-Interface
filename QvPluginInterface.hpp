#pragma once

#include <QFlags>
#include <QIcon>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QWidget>

constexpr auto QV2RAY_PLUGIN_INTERFACE_VERSION = 1;

enum QV2RAY_PLUGIN_HOOK_TYPE
{
    NONE,
    /// This plugin listens on group (Creation, Renaming, Modifying, Updating (subscription) and Removing)
    /// and connection               (Creation, Renaming, Modifying, Latency Testing and Removing)
    CONFIG_EVENTS,
    /// This plugin listens on connection Pre-Connect, Post-Connection, Pre-Disconnect and Post-Disconnect
    CONFIG_STATE_EVENTS,
    /// This plugin listens on statistics event
    STATS_EVENTS
};

enum QV2RAY_PLUGIN_HOOK_SUBTYPE
{
    CREATED,
    RENAMED,
    MODIFIED,
    UPDATED,
    REMOVED,
    //
    LATENCY_UPDATED,
    PRE_CONNECTING,
    POST_CONNECTED,
    PRE_DISCONNECTING,
    POST_DISCONNECTED,
    //
    STATS_CHANGED
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
    /// The plugin does not have an UI
    TYPE_NO_UI,
    /// The plugin has an UI in the Preference Window
    TYPE_PREFERENCE_WINDOW,
    /// The plugin has an UI in the Outbound Editor
    TYPE_OUTBOUND_EDITOR,
    /// The plugin has an UI in the Inbound Editor
    TYPE_INBOUND_EDITOR,
    /// The plugin has an UI in the Group Editor
    TYPE_GROUP_EDITOR
};

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
    virtual const QMap<QV2RAY_PLUGIN_UI_TYPE, QWidget *> GetUIWidgets() = 0;
    /// If the plugin is a kernel,
    virtual QObject *GetKernelInstance() = 0;
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

QT_BEGIN_NAMESPACE
#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"
Q_DECLARE_INTERFACE(Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
