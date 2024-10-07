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

void QSigMFAnnotation::AddAnnotation()
{
    m_annotVect.insert(m_annotVect.end(), m_sigmfCore.GetAnnotationValues());
}
