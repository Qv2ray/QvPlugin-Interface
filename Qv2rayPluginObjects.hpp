#pragma once
#include "QvPluginInterfaceModels.hpp"

#include <QIcon>
#include <QJsonObject>
#include <QObject>
#include <QWidget>

namespace Qv2rayPlugin
{
    struct QvPluginMetadata
    {
        QString Name;
        QString Author;
        QString InternalName;
        QString Description;
        QIcon Icon;
        //
        CAPABILITY_FLAGS Capabilities;
        SPECIAL_TYPE_FLAGS SpecialPluginType;
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
        QvPluginMetadata(){};
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
      public:
        explicit QvPluginKernel(QObject *parent = nullptr) : QObject(parent){};
        // Events handlers
        /// Kernel related operations
        virtual bool StartKernel(const QJsonObject &, const QString &) = 0;
        virtual bool StopKernel() = 0;
        /// Key = DisplayName, Value = protocol.
        virtual const QMap<QString, QString> GetKernelOutbounds() const = 0;
        //
      signals:
        /// Kernel related operations
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvaliable(const QString &);
        void OnKernelStatsAvailable(quint64 _t1, quint64 _t2);
    };
} // namespace Qv2rayPlugin
