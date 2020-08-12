#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <memory>

constexpr auto QV2RAY_PLUGIN_INTERFACE_VERSION = 3;
namespace Qv2rayPlugin
{
    enum class PluginUpdateType
    {
        GITHUB_RELEASE = 0,
        URL = 1
    };

    enum PluginComponentType
    {
        COMPONENT_OUTBOUND_HANDLER = 0,
        COMPONENT_KERNEL = 1,
        COMPONENT_SUBSCRIPTION_ADAPTER = 2,
        COMPONENT_OUTBOUND_EDITOR = 3,
        COMPONENT_INBOUND_EDITOR = 4,
        COMPONENT_MAINWINDOW_WIDGET = 5,
        COMPONENT_EVENT_HANDLER = 6
    };

    enum OutboundInfoFlags
    {
        INFO_DISPLAYNAME = 0,
        INFO_PROTOCOL = 1,
        INFO_SERVER = 2,
        INFO_PORT = 3,
        INFO_SNI = 4
    };

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

    typedef QMap<OutboundInfoFlags, QVariant> OutboundInfoObject;

    struct QvPluginMetadata
    {
        QString Name;
        QString Author;
        QString InternalName;
        QString Description;
        QString VersionString;
        QString UpdateUrl;
        QList<PluginComponentType> Components;
        QvPluginMetadata(const QString &name,                                   //
                         const QString &author,                                 //
                         const QString &internalName,                           //
                         const QString &description,                            //
                         const QString &versionString,                          //
                         const QString &updateUrl,                              //
                         const QList<PluginComponentType> &supportedComponents) //
            : Name(name),                                                       //
              Author(author),                                                   //
              InternalName(internalName),                                       //
              Description(description),                                         //
              VersionString(versionString),                                     //
              UpdateUrl(updateUrl),                                             //
              Components(supportedComponents)                                   //
              {};
        QvPluginMetadata(){};
    };
} // namespace Qv2rayPlugin
