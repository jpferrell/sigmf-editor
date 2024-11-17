#ifndef QSIGMFANNOTATION_H
#define QSIGMFANNOTATION_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "include/qsigmfcore.h"
#include "include/qsigmftypes.h"
#include "include/qcapturedetails.h"
#include "include/qadsb.h"
#include "include/qwifi.h"
#include "include/qantenna.h"
#include "include/qtraceability.h"

class QSigMFAnnotation : public QObject
{
    Q_OBJECT
public:
    QSigMFAnnotation();

    QJsonArray GenerateAnnotationJsonArray();

signals:

    void extensionEnabled(QString name, QString version, QString optional);

public slots:

    void SetSampleStart(int);
    void SetSampleCount(int);
    void SetFrequencyLower(double);
    void SetFrequencyHigher(double);
    void SetLabel(QString);
    void SetComment(QString);
    void SetGenerator(QString);
    void SetUuid(QString);

    void SetCapDetEnabled(bool);
    void SetCapDetSnr(double);
    void SetCapDetSigRefNum(QString);

    void SetAdsbEnabled(bool);
    void SetAdsbDownlinkFrmt(int);
    void SetAdsbMsgType(int);
    void SetIcaAddr(double);
    void SetBinary(QString);

    void SetWifiEnabled(bool en);
    void SetWifiStandard(QString str);
    void SetWifiFrameTypePhy(QString str);
    void SetWifiChannel(int c);
    void SetWifiStartTime(double t);
    void SetWifiStopTime(double t);
    void SetWifiFrameDuration(double t);
    void SetWifiMcs(int m);
    void SetWifiMacFrameType(QString str);
    void SetWifiMacTxAddr(QString str);
    void SetWifiMacRxAddr(QString str);
    void SetWifiTxManf(QString str);
    void SetWifiMacFrame(QString str);
    void SetWifiCrc(QString str);
    void SetWifiStartPkt(double s);
    void SetWifiEndPkt(double s);
    void SetWifiNumSampsPkt(double s);

    void SetAntennaEnabled(bool en);
    void SetAntennaAzAng(double a);
    void SetAntennaElvAng(double a);
    void SetAntennaPolarization(QString str);

    void AddAnnotation();
    void EnableExtension(QString name, QString version, QString optional);


protected:

private:

    QSigMfCore m_sigmfCore;
    QCaptureDetails m_capDets;
    QAdsb m_adsb;
    QWifi m_wifi;
    QAntenna m_ant;
    QTraceability m_trace;
    std::vector< std::vector<sigmfJson_t> > m_annotVect;

};

#endif // QSIGMFANNOTATION_H
