#include "qextension.h"

QExtension::QExtension(QObject *parent)
    : QSigMfBase{parent}
    , m_isEnabled(false)
{
}

void QExtension::SetEnable(bool en)
{
    m_isEnabled = en;
}

bool QExtension::GetEnabled()
{
    return m_isEnabled;
}
