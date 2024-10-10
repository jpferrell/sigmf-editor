#ifndef QCAPTUREDETAILS_H
#define QCAPTUREDETAILS_H

#include <QObject>
#include <QDateTime>

#include "qextension.h"

class QCaptureDetails : public QExtension
{
    Q_OBJECT
public:
    explicit QCaptureDetails(QObject *parent = nullptr);

    // Capture
    void SetAcqScaleFactor(double);
    void SetAttenuation(double);
    void SetAcqBandwidth(double);
    void SetStartCapture(QDateTime);
    void SetStopCapture(QDateTime);
    void SetSourceFile(QString);
    void SetGain(double);

    // Annotations
    void SetSnr(double);
    void SetSigRefNum(QString);

public slots:

protected:

private:
};

#endif // QCAPTUREDETAILS_H
