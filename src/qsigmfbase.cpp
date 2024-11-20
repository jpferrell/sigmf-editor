#include "include/qsigmfbase.h"

/*!
 * \class QSigMfBase
 * \brief The QSigMfBase class that provides the methods for producing vectors
 * of set values.
 * \since v0.0.1
 */

/*!
 * \brief QSigMfBase::QSigMfBase Constructs the QSigMfBase class and initializes required keys
 * vector.
 * \param parent (QObject *)
 */
QSigMfBase::QSigMfBase(qstringVect_t reqGlobeVect, qstringVect_t reqCapVect, qstringVect_t reqAnnotVect, QObject *parent)
    : QObject{parent}
    , m_requiredGlobalKeys(reqGlobeVect)
    , m_requiredCaptureKeys(reqCapVect)
    , m_requiredAnnotKeys(reqAnnotVect)
{
}

sigmfMap_t QSigMfBase::GetGlobalMap()
{
    return _CheckRequiredData(m_globalJsonMap, m_requiredGlobalKeys) ? m_globalJsonMap : sigmfMap_t();
}

sigmfMap_t QSigMfBase::GetCaptureMap()
{
    return _CheckRequiredData(m_captureJsonMap, m_requiredCaptureKeys) ? m_captureJsonMap : sigmfMap_t();
}

sigmfMap_t QSigMfBase::GetAnnotationMap()
{
    return _CheckRequiredData(m_annotJsonMap, m_requiredAnnotKeys) ? m_annotJsonMap : sigmfMap_t();
}

/*!
 * \brief QSigMfBase::_CheckRequiredData checks the passed in vector to validate that JSON keys marked
 * as required are not empty.
 *
 * \param map (sigmfMap_t) holding the JSON keys to be checked.
 *
 * \return \c true if the JSON keys marked as required in the passed map are found.
 */
bool QSigMfBase::_CheckRequiredData(sigmfMap_t map, qstringVect_t requiredKeys)
{
    bool isCorrect = true;
    for (auto it = requiredKeys.cbegin(); it != requiredKeys.cend(); it++) {
        if (map.find(*it)==map.end()) {
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}
