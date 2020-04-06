#pragma once

#include "QvPluginInterfaceModels.hpp"

#include <QObject>

namespace Qv2rayPlugin
{
#define QVPlUGIN_DECL_EVENTHANDLER(type) void ProcessEvent_##type(const Qv##type##EventObject &){};
    class Qv2rayPluginProcessor : public QObject
    {
        Q_OBJECT
      public:
        explicit Qv2rayPluginProcessor(QObject *parent = nullptr) : QObject(parent){};
        QVPlUGIN_DECL_EVENTHANDLER(ConnectionStats);
        QVPlUGIN_DECL_EVENTHANDLER(SystemProxy);
        QVPlUGIN_DECL_EVENTHANDLER(Connectivity);
        QVPlUGIN_DECL_EVENTHANDLER(Item);
    };
#undef QVPlUGIN_DECL_EVENTHANDLER
} // namespace Qv2rayPlugin
