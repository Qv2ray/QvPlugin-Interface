#pragma once
#include <QObject>
#include <QWidget>
namespace Qv2rayPlugin
{
    class Qv2rayPluginEditorWidget : QWidget
    {
        Q_OBJECT
        virtual ~Qv2rayPluginEditorWidget() = default;
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject FinalizeEditing() = 0;
    };

    class Qv2rayKernelPluginObject : public QObject
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
} // namespace Qv2rayPlugin
