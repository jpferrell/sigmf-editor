#include "qsigmfbase.h"

QSigMfBase::QSigMfBase(QObject *parent)
    : QObject{parent}
    , m_globalJsonVect()
    , m_captureJsonVect()
    , m_annotJsonVect()
    , m_globalJsonArray()
    , m_captureJsonArray()
    , m_annotJsonArray()
{

}

sigmfVector_t QSigMfBase::GetGlobalValues()
{
    std::vector<sigmfJson_t> retVect;
    //_UpdateDataType();
    bool isValid = _CheckRequiredData(m_globalJsonVect);

    if (isValid) {
        for (auto it = m_globalJsonVect.begin(); it != m_globalJsonVect.end(); it++) {
            if (it->isRequired) {
                retVect.insert(retVect.end(), *it);
            } else if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

sigmfVector_t QSigMfBase::GetCaptureValues()
{
    std::vector<sigmfJson_t> retVect;
    //_UpdateDataType();
    bool isValid = _CheckRequiredData(m_captureJsonVect);
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_captureJsonVect.begin(); it != m_captureJsonVect.end(); it++) {
            if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

sigmfVector_t QSigMfBase::GetAnnotationValues()
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

void QSigMfBase::InitializeGlobalJsonVect(sigmfVector_t vect)
{
    m_globalJsonVect = vect;
}

void QSigMfBase::InitializeCaptureJsonVect(sigmfVector_t vect)
{
    m_captureJsonVect = vect;
}

void QSigMfBase::InitializeAnnotationJsonVect(sigmfVector_t vect)
{
    m_annotJsonVect = vect;
}

void QSigMfBase::InitializeGlobalJsonArray(sigmfArray_t arr)
{
    m_globalJsonArray = arr;
}

void QSigMfBase::InitializeCaptureJsonArray(sigmfArray_t arr)
{
    m_captureJsonArray = arr;
}

void QSigMfBase::InitializeAnnotationJsonArray(sigmfArray_t arr)
{
    m_captureJsonArray = arr;
}

bool QSigMfBase::_CheckRequiredData(sigmfVector_t vect)
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
