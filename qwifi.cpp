#include "qwifi.h"

QWifi::QWifi(QObject *parent)
    : QObject{parent}
{
}

std::vector<sigmfJson_t> QWifi::GetAnnotationValues()
{
    std::vector<sigmfJson_t> retVect;
    bool isValid = _CheckRequiredData(m_annotJsonVect);
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_annotJsonVect.begin(); it != m_annotJsonVect.end(); it++) {
            if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

void QWifi::SetEnabled(bool en)
{
    m_isEnabled = en;
}

bool QWifi::GetIsEnabled()
{
 return m_isEnabled;
}

void QWifi::SetStandard(QString str)
{
    m_annotJsonVect.at(0).jsonVal = str;
}

void QWifi::SetFrameTypePhy(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}

void QWifi::SetChannel(int c)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(c);
}

void QWifi::SetStartTime(double t)
{
    m_annotJsonVect.at(3).jsonVal = QString::number(t);
}

void QWifi::SetStopTime(double t)
{
    m_annotJsonVect.at(4).jsonVal = QString::number(t);
}

void QWifi::SetFrameDuration(double d)
{
    m_annotJsonVect.at(5).jsonVal = QString::number(d);
}

void QWifi::SetMcs(int m)
{
    m_annotJsonVect.at(6).jsonVal = QString::number(m);
}

void QWifi::SetMacFrameType(QString str)
{
    m_annotJsonVect.at(7).jsonVal = str;
}

void QWifi::SetMacTxAddr(QString str)
{
    m_annotJsonVect.at(8).jsonVal = str;
}

void QWifi::SetMacRxAddr(QString str)
{
    m_annotJsonVect.at(9).jsonVal = str;
}

void QWifi::SetTxManf(QString str)
{
    m_annotJsonVect.at(10).jsonVal = str;
}

void QWifi::SetMacFrame(QString str)
{
    m_annotJsonVect.at(11).jsonVal = str;
}

void QWifi::SetCrc(QString str)
{
    m_annotJsonVect.at(12).jsonVal = str;
}

void QWifi::SetStartPkt(double s)
{
    m_annotJsonVect.at(13).jsonVal = QString::number(s);
}

void QWifi::SetEndPkt(double s)
{
    m_annotJsonVect.at(14).jsonVal = QString::number(s);
}

void QWifi::SetNumSampsPkt(double s)
{
    m_annotJsonVect.at(15).jsonVal = QString::number(s);
}

bool QWifi::_CheckRequiredData(std::vector<sigmfJson_t> vect)
{
    bool isCorrect = true;

    for (auto it = vect.begin(); it != vect.end(); it++) {
        if (it->isRequired && !it->jsonVal.compare("")) {
            // If the element is required but is empty, the spec is not fulfilled
            qDebug() << "value is not defined: " << it->jsonKey;
            qDebug() << "Value of " << it->jsonVal;
            isCorrect = false;
        }
    }
    return isCorrect;
}
