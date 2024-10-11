#include "qextension.h"

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
