#ifndef QEXTENSION_H
#define QEXTENSION_H

#include <QObject>
#include <QJsonObject>

#include "include/qsigmfbase.h"

class QExtension : public QSigMfBase
{
    Q_OBJECT
public:
    explicit QExtension(QObject *parent = nullptr);

    sigmfVector_t GetGlobalValues();

    void SetEnable(bool en);
    bool GetEnabled();

    void SetGlobalExtensionObject(QString name, QString version, bool optional);
    QJsonObject GetGlobalExtensionObject();
    bool GetExtensionOptional(){return m_optional;}
    QString GetExtensionName(){return m_name;}
    QString GetExtensionVersion(){return m_version;}

signals:

    void extensionEnabled(QString name, QString version, QString optional);

public slots:

protected:

private:

    bool m_isEnabled;

    QString m_name;
    QString m_version;
    bool m_optional;

};

#endif // QEXTENSION_H
