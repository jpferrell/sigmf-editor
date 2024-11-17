#include "include/qextension.h"

/*!
 * \class QExtension
 * \since v0.0.1
 * \brief The QExtension class that allows for checking if extension SigMF modules are enabled.
 */

/*!
 * \brief QExtension::QExtension constructs the QExtension class and initializes the class as
 * NOT enabled.
 *
 * \param parent (QObject *)
 */
QExtension::QExtension(QObject *parent)
    : QSigMfBase{parent}
    , m_isEnabled(false)
{
}

sigmfVector_t QExtension::GetGlobalValues()
{
    sigmfVector_t retVect = QSigMfBase::GetGlobalValues();
    QString opt = m_optional ? "true" : "false";
    emit extensionEnabled(m_name, m_version, opt);

    return retVect;
}

/*!
 * \brief QExtension::SetEnable sets the extension as enabled or not.
 *
 * \param en \c true to enable the class.
 */
void QExtension::SetEnable(bool en)
{
    m_isEnabled = en;
}

/*!
 * \brief QExtension::GetEnabled gets if the extension is enabled or not.
 * \return  \c true if class is enabled.
 */
bool QExtension::GetEnabled()
{
    return m_isEnabled;
}

void QExtension::SetGlobalExtensionObject(QString name, QString version, bool optional)
{
    m_name = name;
    m_version = version;
    m_optional = optional;
}

QJsonObject QExtension::GetGlobalExtensionObject()
{
    QJsonObject retObj;
    retObj.insert("name", m_name);
    retObj.insert("version", m_version);
    retObj.insert("optional", m_optional);

    return retObj;
}
