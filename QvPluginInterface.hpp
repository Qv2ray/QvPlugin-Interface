#pragma once

#include <QObject>
#include <QString>

class Qv2rayInterface
{
  public:
    virtual ~Qv2rayInterface() = default;
    virtual QString Name() = 0;
    virtual QString Author() = 0;
};

QT_BEGIN_NAMESPACE

#define Qv2rayInterface_IID "com.github.Qv2ray.Qv2rayPluginInterface"

Q_DECLARE_INTERFACE(Qv2rayInterface, Qv2rayInterface_IID)
QT_END_NAMESPACE
