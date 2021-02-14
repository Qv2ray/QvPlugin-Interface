#pragma once
#include <QObject>

namespace Qv2rayPlugin::handlers::kernel
{
    enum KernelOptionFlags
    {
        KERNEL_HTTP_ENABLED,
        KERNEL_HTTP_PORT,
        KERNEL_SOCKS_ENABLED,
        KERNEL_SOCKS_PORT,
        KERNEL_SOCKS_UDP_ENABLED,
        KERNEL_SOCKS_LOCAL_ADDRESS,
        KERNEL_LISTEN_ADDRESS
    };

    class PluginKernel : public QObject
    {
        Q_OBJECT
      public:
        explicit PluginKernel() : QObject(){};
        virtual ~PluginKernel(){};
        virtual void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const QJsonObject &connectionInfo) = 0;
        virtual bool StartKernel() = 0;
        virtual bool StopKernel() = 0;
        virtual QString GetKernelName() const = 0;

      signals:
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvailable(const QString &);
        void OnKernelStatsAvailable(quint64 upSpeed, quint64 downSpeed);

      private:
        QString __qvKernelId;
    };

    class PluginKernelHandler
    {
      public:
        virtual std::unique_ptr<PluginKernel> CreateKernel() const = 0;
        virtual QList<QString> GetKernelProtocols() const = 0;
    };
} // namespace Qv2rayPlugin::handlers::kernel

using namespace Qv2rayPlugin::handlers::kernel;
