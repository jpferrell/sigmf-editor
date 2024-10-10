#include "qcapturedetails.h"

QCaptureDetails::QCaptureDetails(QObject *parent):
    QExtension{parent}
{
    InitializeCaptureJsonVect({
                                  {"capture_details:acq_scale_factor", "", true},
                                  {"capture_details:attenuation", "", true},
                                  {"capture_details:acquisition_bandwidth", "", true},
                                  {"capture_details:start_capture", "", true},
                                  {"capture_details:stop_capture", "", true},
                                  {"capture_details:source_file", "", true},
                                  {"capture_details:gain", "", false}
                              });
    InitializeAnnotationJsonVect({
                                     {"capture_details:SNRdB", "", true},
                                     {"capture_details:signal_reference_number", "", true}
                                 });
}

void QCaptureDetails::SetAcqScaleFactor(double fact)
{
    m_captureJsonVect.at(0).jsonVal = QString::number(fact);
}

void QCaptureDetails::SetAttenuation(double att)
{
    m_captureJsonVect.at(1).jsonVal = QString::number(att);
}

void QCaptureDetails::SetAcqBandwidth(double bw)
{
    m_captureJsonVect.at(2).jsonVal = QString::number(bw);
}

void QCaptureDetails::SetStartCapture(QDateTime dt)
{
    m_captureJsonVect.at(3).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QCaptureDetails::SetStopCapture(QDateTime dt)
{
    m_captureJsonVect.at(4).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QCaptureDetails::SetSourceFile(QString str)
{
    m_captureJsonVect.at(5).jsonVal = str;
}

void QCaptureDetails::SetGain(double gain)
{
    m_captureJsonVect.at(6).jsonVal = QString::number(gain);
}

void QCaptureDetails::SetSnr(double snr)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(snr);
}

void QCaptureDetails::SetSigRefNum(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}
