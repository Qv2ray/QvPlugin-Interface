#pragma once

#include <QJsonObject>
#include <QMap>

namespace Qv2rayPlugin::handlers::outbound
{
    enum OutboundInfoFlags
    {
        INFO_DISPLAYNAME = 0,
        INFO_PROTOCOL = 1,
        INFO_SERVER = 2,
        INFO_PORT = 3,
        INFO_SNI = 4
    };

    typedef QMap<OutboundInfoFlags, QVariant> OutboundInfoObject;

    class PluginOutboundHandler
    {
      public:
        explicit PluginOutboundHandler(){};
        virtual const QString SerializeOutbound(const QString &protocol,   //
                                                const QString &alias,      //
                                                const QString &groupName,  //
                                                const QJsonObject &object, //
                                                const QJsonObject &streamSettings) const = 0;
        virtual const QPair<QString, QJsonObject> DeserializeOutbound(const QString &link, QString *alias, QString *errorMessage) const = 0;
        virtual const OutboundInfoObject GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const = 0;
        virtual void SetOutboundInfo(const QString &protocol, const OutboundInfoObject &info, QJsonObject &outbound) const = 0;
        virtual const QList<QString> SupportedProtocols() const = 0;
        virtual const QList<QString> SupportedLinkPrefixes() const = 0;
    };
} // namespace Qv2rayPlugin::handlers::outbound

using namespace ::Qv2rayPlugin::handlers::outbound;
