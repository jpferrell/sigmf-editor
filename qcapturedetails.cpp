#include "qcapturedetails.h"

QCaptureDetails::QCaptureDetails():
    m_isEnabled(false)
  , m_capJsonArr()
  , m_annotJsonArr()
{
}

std::vector<sigmfJson_t> QCaptureDetails::GetCaptureValues()
{
    std::vector<sigmfJson_t> retVect;
    // Is this redundant?
    bool isValid = _CheckRequiredData(m_capJsonVect);
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_capJsonVect.begin(); it != m_capJsonVect.end(); it++) {
            if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

std::vector<sigmfJson_t> QCaptureDetails::GetAnnotationValues()
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

void QCaptureDetails::SetAcqScaleFactor(double fact)
{
    m_capJsonVect.at(0).jsonVal = QString::number(fact);
}

void QCaptureDetails::SetAttenuation(double att)
{
    m_capJsonVect.at(1).jsonVal = QString::number(att);
}

void QCaptureDetails::SetAcqBandwidth(double bw)
{
    m_capJsonVect.at(2).jsonVal = QString::number(bw);
}

void QCaptureDetails::SetStartCapture(QDateTime dt)
{
    m_capJsonVect.at(3).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QCaptureDetails::SetStopCapture(QDateTime dt)
{
    m_capJsonVect.at(4).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QCaptureDetails::SetSourceFile(QString str)
{
    m_capJsonVect.at(5).jsonVal = str;
}

void QCaptureDetails::SetGain(double gain)
{
    m_capJsonVect.at(6).jsonVal = QString::number(gain);
}

bool QCaptureDetails::GetIsEnabled()
{
    return m_isEnabled;
}

void QCaptureDetails::SetSnr(double snr)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(snr);
}

void QCaptureDetails::SetSigRefNum(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}

void QCaptureDetails::SetEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
}

void QCaptureDetails::AddCapture()
{
    bool isValid = _CheckRequiredData(m_capJsonVect);
    if (isValid && m_isEnabled) {
        m_capJsonArr.insert(m_capJsonArr.end(), m_capJsonVect);
    }
}

void QCaptureDetails::AddAnnotation()
{
    bool isValid = _CheckRequiredData(m_annotJsonVect);
    if (isValid && m_isEnabled) {
        m_annotJsonArr.insert(m_annotJsonArr.end(), m_annotJsonVect);
    }
}

bool QCaptureDetails::_CheckRequiredData(std::vector<sigmfJson_t> vect)
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
