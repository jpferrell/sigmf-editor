#include "qsigmfannotation.h"

QSigMFAnnotation::QSigMFAnnotation():
    m_sigmfCore()
  , m_annotVect()
{

}

QJsonArray QSigMFAnnotation::GenerateAnnotationJsonArray()
{
    QJsonArray retArr;

    std::sort(m_annotVect.begin(), m_annotVect.end(), [](const std::vector<sigmfJson_t> &lhs, const std::vector<sigmfJson_t> &rhs) {
        return lhs.at(0).jsonVal.toInt() < rhs.at(0).jsonVal.toInt();
    });
    for (auto outIt = m_annotVect.begin(); outIt != m_annotVect.end(); outIt++) {
        QJsonObject obj;
        for (auto inIt = outIt->begin(); inIt != outIt->end(); inIt++) {
            obj.insert(inIt->jsonKey, inIt->jsonVal);
            qDebug() << "inserted: " << inIt->jsonKey;
        }
        retArr.append(obj);
    }

    return retArr;
}

void QSigMFAnnotation::SetSampleStart(int sr)
{
    m_sigmfCore.SetAnnotSampleStart(sr);
}

void QSigMFAnnotation::SetSampleCount(int sc)
{
    m_sigmfCore.SetSampleCount(sc);
}

void QSigMFAnnotation::SetFrequencyLower(double f)
{
    m_sigmfCore.SetFrequencyLower(f);
}

void QSigMFAnnotation::SetFrequencyHigher(double f)
{
    m_sigmfCore.SetFrequencyHigher(f);
}

void QSigMFAnnotation::SetLabel(QString str)
{
    m_sigmfCore.SetLabel(str);
}

void QSigMFAnnotation::SetComment(QString str)
{
    m_sigmfCore.SetComment(str);
}

void QSigMFAnnotation::SetGenerator(QString str)
{
    m_sigmfCore.SetGenerator(str);
}

void QSigMFAnnotation::SetUuid(QString str)
{
    m_sigmfCore.SetUuid(str);
}

void QSigMFAnnotation::SetCapDetEnabled(bool isEnabled)
{
    m_capDets.SetEnabled(isEnabled);
}

void QSigMFAnnotation::SetCapDetSnr(double num)
{
    m_capDets.SetSnr(num);
}

void QSigMFAnnotation::SetCapDetSigRefNum(QString str)
{
    m_capDets.SetSigRefNum(str);
}

void QSigMFAnnotation::AddAnnotation()
{
    // Had to do this to get it all within the same array
    std::vector<sigmfJson_t> tmp;
    std::vector<sigmfJson_t> sigVect = m_sigmfCore.GetAnnotationValues();
    for (auto it = sigVect.begin(); it != sigVect.end(); it++) {
        tmp.emplace_back(*it);
    }
    if (m_capDets.GetIsEnabled()) {
        std::vector<sigmfJson_t> detVect = m_capDets.GetAnnotationValues();
        for (auto it = detVect.begin(); it != detVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    m_annotVect.insert(m_annotVect.end(), tmp);
    /*
    m_annotVect.insert(m_annotVect.end(), m_sigmfCore.GetAnnotationValues());
    if (m_capDets.GetIsEnabled()) {
        m_annotVect.insert(m_annotVect.end(), m_capDets.GetAnnotationValues());
    }
    */
}
