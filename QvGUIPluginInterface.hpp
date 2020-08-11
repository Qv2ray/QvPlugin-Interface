#pragma once
#include "QvPluginBase.hpp"

#include <QWidgets>

namespace Qv2rayPlugin
{
    class QvPluginEditor : public QWidget
    {
        Q_OBJECT
      public:
        explicit QvPluginEditor(QWidget *parent = nullptr) : QWidget(parent){};
        //
        virtual void SetHostInfo(const QString &address, int port) = 0;
        virtual QPair<QString, int> GetHostInfo() const = 0;
        //
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject GetContent() const = 0;
        //
        virtual void SwitchOutbound(const QString &) = 0;
        virtual QList<QvPluginOutboundProtocolObject> OutboundCapabilities() const = 0;
    };

} // namespace Qv2rayPlugin
