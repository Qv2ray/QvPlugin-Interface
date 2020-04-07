#pragma once
#include "QvPluginInterfaceModels.hpp"

#include <QIcon>
#include <QObject>
#include <QWidget>
namespace Qv2rayPlugin
{
    struct QvPluginMetadata
    {
        const QString Name;
        const QString Author;
        const QString InternalName;
        const QString Description;
        const QIcon Icon;
        //
        const CAPABILITY_FLAGS Capabilities;
        const SPECIAL_TYPE_FLAGS SpecialPluginType;
        QvPluginMetadata(const QString &name,                    //
                         const QString &author,                  //
                         const QString &internalName,            //
                         const QString &description,             //
                         const QIcon &icon,                      //
                         const CAPABILITY_FLAGS &caps,           //
                         const SPECIAL_TYPE_FLAGS &specialTypes) //
            : Name(name),                                        //
              Author(author),                                    //
              InternalName(internalName),                        //
              Description(description),                          //
              Icon(icon),                                        //
              Capabilities(caps),                                //
              SpecialPluginType(specialTypes)
        {
        }
    };

    class QvPluginEditor : QWidget
    {
        Q_OBJECT
        virtual ~QvPluginEditor() = default;
        virtual void SetContent(const QJsonObject &) = 0;
        virtual const QJsonObject FinalizeEditing() = 0;
    };

    class QvPluginKernel : public QObject
    {
        Q_OBJECT
        // Events handlers
        /// Kernel related operations
        virtual bool StartKernel(const QJsonObject) = 0;
        virtual bool StopKernel() = 0;
        //
        /// A list of valid outbounds where this plugin is capable to handle, if any.
        virtual QStringList OutboundTypes() const = 0;

      signals:
        /// Kernel related operations
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvaliable(const QString &);
    };
} // namespace Qv2rayPlugin
