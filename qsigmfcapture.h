#ifndef QSIGMFCAPTURE_H
#define QSIGMFCAPTURE_H

#include <QObject>
#include <QJsonArray>

#include "qsigmfcore.h"
#include "qsigmftypes.h"

class QSigMFCapture : public QObject
{
    Q_OBJECT
public:
    QSigMFCapture();

    QJsonObject GenerateCaptureJson();
    QJsonArray GenerateCaptureJsonArray();

public slots:

    void SetSampleStart(int);
    void SetDatetime(QDateTime);
    void SetFrequency(double);
    void SetGlobalIndex(int);
    void SetHeaderBytes(int);
    void SetDatetimeEnabled(bool);
    void AddCapture();

protected:

private:

    QSigMfCore m_sigmfCore;
    std::vector< std::vector <sigmfJson_t> > m_captureVect;

};

#endif // QSIGMFCAPTURE_H
