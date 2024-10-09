#include "qadsb.h"

QAdsb::QAdsb(QObject *parent)
    : QObject{parent}
{
}

std::vector<sigmfJson_t> QAdsb::GetAnnotationValues()
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

void QAdsb::SetEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
}

void QAdsb::SetDownlinkFrmt(int num)
{
    m_annotJsonVect.at(0).jsonVal = num == 0 ? "11" : "17";
}

void QAdsb::SetMessageType(int num)
{
    m_annotJsonVect.at(1).jsonVal = QString::number(num);
}

void QAdsb::SetIcaAddr(double d)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(d);
}

void QAdsb::SetBinary(QString str)
{
    m_annotJsonVect.at(3).jsonVal = str;
}

bool QAdsb::GetIsEnabled()
{
    return m_isEnabled;
}

bool QAdsb::_CheckRequiredData(std::vector<sigmfJson_t> vect)
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
