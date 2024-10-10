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
    m_capDets.SetEnable(isEnabled);
}

void QSigMFAnnotation::SetCapDetSnr(double num)
{
    m_capDets.SetSnr(num);
}

void QSigMFAnnotation::SetCapDetSigRefNum(QString str)
{
    m_capDets.SetSigRefNum(str);
}

void QSigMFAnnotation::SetAdsbEnabled(bool isEnabled)
{
    m_adsb.SetEnable(isEnabled);
}

void QSigMFAnnotation::SetAdsbDownlinkFrmt(int num)
{
    m_adsb.SetDownlinkFrmt(num);
}

void QSigMFAnnotation::SetAdsbMsgType(int num)
{
    m_adsb.SetMessageType(num);
}

void QSigMFAnnotation::SetIcaAddr(double addr)
{
    m_adsb.SetIcaAddr(addr);
}

void QSigMFAnnotation::SetBinary(QString str)
{
    m_adsb.SetBinary(str);
}

void QSigMFAnnotation::SetWifiEnabled(bool en)
{
    m_wifi.SetEnable(en);
}

void QSigMFAnnotation::SetWifiStandard(QString str)
{
    m_wifi.SetStandard(str);
}

void QSigMFAnnotation::SetWifiFrameTypePhy(QString str)
{
    m_wifi.SetFrameTypePhy(str);
}

void QSigMFAnnotation::SetWifiChannel(int c)
{
    m_wifi.SetChannel(c);
}

void QSigMFAnnotation::SetWifiStartTime(double t)
{
    m_wifi.SetStartTime(t);
}

void QSigMFAnnotation::SetWifiStopTime(double t)
{
    m_wifi.SetStopTime(t);
}

void QSigMFAnnotation::SetWifiFrameDuration(double t)
{
    m_wifi.SetFrameDuration(t);
}

void QSigMFAnnotation::SetWifiMcs(int m)
{
    m_wifi.SetMcs(m);
}

void QSigMFAnnotation::SetWifiMacFrameType(QString str)
{
    m_wifi.SetMacFrameType(str);
}

void QSigMFAnnotation::SetWifiMacTxAddr(QString str)
{
    m_wifi.SetMacTxAddr(str);
}

void QSigMFAnnotation::SetWifiMacRxAddr(QString str)
{
    m_wifi.SetMacRxAddr(str);
}

void QSigMFAnnotation::SetWifiTxManf(QString str)
{
    m_wifi.SetTxManf(str);
}

void QSigMFAnnotation::SetWifiMacFrame(QString str)
{
    m_wifi.SetMacFrame(str);
}

void QSigMFAnnotation::SetWifiCrc(QString str)
{
    m_wifi.SetCrc(str);
}

void QSigMFAnnotation::SetWifiStartPkt(double s)
{
    m_wifi.SetStartPkt(s);
}

void QSigMFAnnotation::SetWifiEndPkt(double s)
{
    m_wifi.SetEndPkt(s);
}

void QSigMFAnnotation::SetWifiNumSampsPkt(double s)
{
    m_wifi.SetNumSampsPkt(s);
}

void QSigMFAnnotation::SetAntennaEnabled(bool en)
{
    qDebug() << "antenna: " << en;
    m_ant.SetEnable(en);
}

void QSigMFAnnotation::SetAntennaAzAng(double a)
{
    m_ant.SetAzimuthAng(a);
}

void QSigMFAnnotation::SetAntennaElvAng(double a)
{
    m_ant.SetElvAng(a);
}

void QSigMFAnnotation::SetAntennaPolarization(QString str)
{
    m_ant.SetPolarization(str);
}

void QSigMFAnnotation::AddAnnotation()
{
    // Had to do this to get it all within the same array
    std::vector<sigmfJson_t> tmp;
    std::vector<sigmfJson_t> sigVect = m_sigmfCore.GetAnnotationValues();
    for (auto it = sigVect.begin(); it != sigVect.end(); it++) {
        tmp.emplace_back(*it);
    }
    if (m_capDets.GetEnabled()) {
        std::vector<sigmfJson_t> detVect = m_capDets.GetAnnotationValues();
        for (auto it = detVect.begin(); it != detVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    if (m_adsb.GetEnabled()) {
        std::vector<sigmfJson_t> adsbVect = m_adsb.GetAnnotationValues();
        for (auto it = adsbVect.begin(); it != adsbVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    if (m_wifi.GetEnabled()) {
        std::vector<sigmfJson_t> wifiVect = m_wifi.GetAnnotationValues();
        for (auto it = wifiVect.begin(); it != wifiVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    qDebug() << "m_ant enabled: " << m_ant.GetEnabled();
    if (m_ant.GetEnabled()) {
        sigmfVector_t antVect = m_ant.GetAnnotationValues();
        for (auto it = antVect.begin(); it != antVect.end(); it++) {
            tmp.emplace_back(*it);
        }
    }
    m_annotVect.insert(m_annotVect.end(), tmp);
}
