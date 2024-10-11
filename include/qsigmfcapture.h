#ifndef QSIGMFCAPTURE_H
#define QSIGMFCAPTURE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "include/qsigmfcore.h"
#include "include/qcapturedetails.h"
#include "include/qsigmftypes.h"

class QSigMFCapture : public QObject
{
    Q_OBJECT
public:
    QSigMFCapture();

    QJsonArray GenerateCaptureJsonArray();

public slots:

    void SetSampleStart(int);
    void SetDatetime(QDateTime);
    void SetFrequency(double);
    void SetGlobalIndex(int);
    void SetHeaderBytes(int);
    void SetDatetimeEnabled(bool);

    void SetAcqScaleFactor(double);
    void SetAttenuation(double);
    void SetAcqBandwidth(double);
    void SetStartCapture(QDateTime);
    void SetStopCapture(QDateTime);
    void SetSourceFile(QString);
    void SetGain(double);

    void SetDetsEnabled(bool);

    void AddCapture();

protected:

private:

    QSigMfCore m_sigmfCore;
    QCaptureDetails m_capDets;
    std::vector< std::vector <sigmfJson_t> > m_captureVect;

};

#endif // QSIGMFCAPTURE_H
