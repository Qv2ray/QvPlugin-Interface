#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QObject>

#define QVPlUGIN_DECL_EVENT_HANDLER(type) virtual void ProcessEvent_##type(const ::Qv2rayPlugin::Qv##type##EventObject &)
#define QVPlUGIN_DECL_EVENT_HANDLER_OVERRIDE(type) QVPlUGIN_DECL_EVENT_HANDLER(type) override
namespace Qv2rayPlugin
{
    class QvPluginEventHandler : public QObject
    {
        Q_OBJECT
      public:
        explicit QvPluginEventHandler(QObject *parent = nullptr) : QObject(parent){};
        QVPlUGIN_DECL_EVENT_HANDLER(ConnectionStats){};
        QVPlUGIN_DECL_EVENT_HANDLER(SystemProxy){};
        QVPlUGIN_DECL_EVENT_HANDLER(Connectivity){};
        QVPlUGIN_DECL_EVENT_HANDLER(ConnectionEntry){};
    };
} // namespace Qv2rayPlugin
