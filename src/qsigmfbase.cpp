#include "include/qsigmfbase.h"

/*!
 * \class QSigMfBase
 * \brief The QSigMfBase class that provides the methods for producing vectors
 * of set values.
 * \since v0.0.1
 */

/*!
 * \brief QSigMfBase::QSigMfBase Constructs the QSigMfBase class and initializes the vectors
 * to be empty.
 * \param parent (QObject *)
 */
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

/*!
 * \brief QSigMfBase::GetGlobalValues returns a vector holding the global JSON values
 * \return sigmfVector_t holding the populated JSON values.
 */
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

/*!
 * \brief QSigMfBase::GetCaptureValues returns a vector holding the capture JSON values.
 * \return sigmfVector_t holding the populated capture JSON values.
 */
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

/*!
 * \brief QSigMfBase::GetAnnotationValues returns a vector holding the annotation JSON values
 * \return sigmfVector_t holding the populated annotation JSON values.
 */
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

/*!
 * \brief QSigMfBase::InitializeGlobalJsonVect initializes the global JSON vector.
 *
 * This implementation allows for different JSON keys and required keys to be used based on
 * the SigMF extension.
 *
 * \param vect (sigmfVector_t) that holds the JSON keys (and default JSON values), along with
 * whether the Key is required to be filled.
 */
void QSigMfBase::InitializeGlobalJsonVect(sigmfVector_t vect)
{
    m_globalJsonVect = vect;
}

/*!
 * \brief QSigMfBase::InitializeCaptureJsonVect initializes the capture JSON vector.
 *
 * This implementation allows for different JSON keys and required keys to be used based on
 * the SigMF extension.
 *
 * \param vect (sigmfVector_t) that holds the JSON keys (and default JSON values), along with
 * whether the Key is required to be filled.
 */
void QSigMfBase::InitializeCaptureJsonVect(sigmfVector_t vect)
{
    m_captureJsonVect = vect;
}

/*!
 * \brief QSigMfBase::InitializeAnnotationJsonVect initializes the annotation JSON vector.
 *
 * This implementation allows for different JSON keys and required keys to be used based on
 * the SigMF extension.
 *
 * \param vect (sigmfVector_t) that holds the JSON keys (and default JSON values), along with
 * whether the Key is required to be filled.
 */
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

/*!
 * \brief QSigMfBase::_CheckRequiredData checks the passed in vector to validate that JSON keys marked
 * as required are not empty.
 *
 * \param vect (sigmfVector_t) holding the JSON keys and values to be checked.
 *
 * \return \c true if the JSON keys marked as required in the passed array are not empty.
 */
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
