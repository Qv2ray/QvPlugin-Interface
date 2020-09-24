#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QJsonObject>
#include <QObject>

namespace Qv2rayPlugin
{
    class PluginOutboundHandler
    {
      public:
        explicit PluginOutboundHandler(){};
        virtual const QString SerializeOutbound(const QString &protocol,  //
                                                const QString &alias,     //
                                                const QString &groupName, //
                                                const QJsonObject &object) const = 0;
        virtual const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const = 0;
        virtual const OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const = 0;
        virtual const QList<QString> SupportedProtocols() const = 0;
        virtual const QList<QString> SupportedLinkPrefixes() const = 0;
    };

    class PluginSubscriptionAdapter
    {
      public:
        explicit PluginSubscriptionAdapter(){};
        virtual ~PluginSubscriptionAdapter(){};
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
        //
      signals:
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvailable(const QString &);
        void OnKernelStatsAvailable(quint64 upSpeed, quint64 downSpeed);

      private:
        QString __qvKernelId;
    };

    class PluginKernelInterface
    {
      public:
        virtual std::unique_ptr<PluginKernel> CreateKernel() const = 0;
        virtual QList<QString> GetKernelProtocols() const = 0;
    };

    template<typename ...T> class Qp;

    template<typename ...T>
    class Qp
    {
    public:
         void ProcessEvent(){}
    };

#define DEFAULT_IMPLEMENT ;

    template<typename T1,typename ...T2>
    class Qp<T1,T2...> : public Qp<T2...>
    {
    public:
        using Qp<T2...>::ProcessEvent;
        virtual void ProcessEvent(const T1 &pluginEvent){DEFAULT_IMPLEMENT};
    };

    using namespace ::Qv2rayPlugin::Events;

    class PluginEventHandler :public Qp<Connectivity::EventObject,
                                          SystemProxy::EventObject,
                                          ConnectionEntry::EventObject,
                                          ConnectionStats::EventObject>
    {
    };

} // namespace Qv2rayPlugin
