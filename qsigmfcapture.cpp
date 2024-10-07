#include "qsigmfcapture.h"

QSigMFCapture::QSigMFCapture():
    m_sigmfCore()
  , m_captureVect()
{

}

QJsonObject QSigMFCapture::GenerateCaptureJson()
{
    QJsonObject retObj;

    std::vector<sigmfJson_t> capVect = m_sigmfCore.GetCaptureValues();
    for (auto it = capVect.begin(); it != capVect.end(); it++) {
        retObj.insert(it->jsonKey, it->jsonVal);
        qDebug() << "inserted " << it->jsonKey;
    }

    return retObj;
}

QJsonArray QSigMFCapture::GenerateCaptureJsonArray()
{
    QJsonArray retArr;

    std::sort(m_captureVect.begin(), m_captureVect.end(), [](const std::vector<sigmfJson_t> &lhs, const std::vector<sigmfJson_t> &rhs) {
        return lhs.at(0).jsonVal.toInt() < rhs.at(0).jsonVal.toInt();
    });
    for (auto outIt = m_captureVect.begin(); outIt != m_captureVect.end(); outIt++) {
        QJsonObject obj;
        for (auto inIt = outIt->begin(); inIt != outIt->end(); inIt++) {
            obj.insert(inIt->jsonKey, inIt->jsonVal);
        }
        retArr.append(obj);
    }

    return retArr;
}

void QSigMFCapture::SetSampleStart(int idx)
{
    m_sigmfCore.SetSampleStart(idx);
}

void QSigMFCapture::SetDatetime(QDateTime dt)
{
    m_sigmfCore.SetDatetime(dt);
}

void QSigMFCapture::SetFrequency(double freq)
{
    m_sigmfCore.SetFrequency(freq);
}

void QSigMFCapture::SetGlobalIndex(int idx)
{
    m_sigmfCore.SetGlobalIndex(idx);
}

void QSigMFCapture::SetHeaderBytes(int num)
{
    m_sigmfCore.SetHeaderBytes(num);
}

void QSigMFCapture::SetDatetimeEnabled(bool isEnabled)
{
    m_sigmfCore.SetDatetimeEnabled(isEnabled);
}

void QSigMFCapture::AddCapture()
{
    qDebug() << "QSigMFCapture::AddCapture";
    m_captureVect.insert(m_captureVect.end(), m_sigmfCore.GetCaptureValues());
}
