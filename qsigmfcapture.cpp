#include "qsigmfcapture.h"

QSigMFCapture::QSigMFCapture():
    m_sigmfCore()
  , m_captureVect()
{
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

void QSigMFCapture::SetAcqScaleFactor(double num)
{
    m_capDets.SetAcqScaleFactor(num);
}

void QSigMFCapture::SetAttenuation(double num)
{
    m_capDets.SetAttenuation(num);
}

void QSigMFCapture::SetAcqBandwidth(double num)
{
    m_capDets.SetAcqBandwidth(num);
}

void QSigMFCapture::SetStartCapture(QDateTime dt)
{
    m_capDets.SetStartCapture(dt);
}

void QSigMFCapture::SetStopCapture(QDateTime dt)
{
    m_capDets.SetStopCapture(dt);
}

void QSigMFCapture::SetSourceFile(QString str)
{
    m_capDets.SetSourceFile(str);
}

void QSigMFCapture::SetGain(double num)
{
    m_capDets.SetGain(num);
}

void QSigMFCapture::SetDetsEnabled(bool isEnabled)
{
    m_capDets.SetEnable(isEnabled);
}

void QSigMFCapture::AddCapture()
{
    // Had to do this to get it all within the same array
    std::vector<sigmfJson_t> tmp;
    std::vector<sigmfJson_t> sigVect = m_sigmfCore.GetCaptureValues();
    for (auto it = sigVect.begin(); it != sigVect.end(); it++) {
        tmp.emplace_back(*it);
    }
    if (m_capDets.GetEnabled()) {
        std::vector<sigmfJson_t> detVect = m_capDets.GetCaptureValues();
        for (auto it = detVect.begin(); it != detVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    m_captureVect.insert(m_captureVect.end(), tmp);
}
