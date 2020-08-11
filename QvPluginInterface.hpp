#pragma once

#include "QvPluginBase.hpp"
#include "QvPluginProcessor.hpp"
namespace Qv2rayPlugin
{
    class Qv2rayPluginGUIFactory;

    class Qv2rayInterface;
    inline Qv2rayInterface *pluginInstance = nullptr;

    class Qv2rayInterface
    {
        friend class PluginOutboundHandler;
        friend class PluginKernel;
        friend class PluginEventHandler;
        friend class Qv2rayPluginGUIFactory;

      public:
        const int QvPluginInterfaceVersion = QV2RAY_PLUGIN_INTERFACE_VERSION;

        virtual ~Qv2rayInterface() = default;
        virtual const QvPluginMetadata GetMetadata() const = 0;
        virtual bool InitializePlugin(const QString &, const QJsonObject &) = 0;
        //
        virtual std::shared_ptr<PluginOutboundHandler> GetOutboundHandler() const = 0;
        virtual std::shared_ptr<PluginEventHandler> GetEventHandler() const = 0;
        virtual std::unique_ptr<PluginKernel> CreateKernel() const = 0;
        virtual QList<QString> GetKernelProtocols() const = 0;
        //
        virtual std::unique_ptr<Qv2rayPluginGUIFactory> GetGUIFactory() const = 0;
        //
        // Signals
        virtual void PluginLog(const QString &) const = 0;
        virtual void PluginErrorMessageBox(const QString &title, const QString &message) const = 0;
        virtual void UpdateSettings(const QJsonObject &_settings) final
        {
            settings = _settings;
        }
        virtual const QJsonObject GetSettngs() const final
        {
            return settings;
        }

      protected:
        explicit Qv2rayInterface()
        {
            pluginInstance = this;
        }
        QJsonObject settings;
    };
} // namespace Qv2rayPlugin

QT_BEGIN_NAMESPACE
#define Qv2rayPluginInterfaceCollection_IID "com.github.Qv2ray.Qv2rayPluginCollectionInterface"
Q_DECLARE_INTERFACE(Qv2rayPlugin::Qv2rayInterface, Qv2rayPluginInterfaceCollection_IID)
QT_END_NAMESPACE
