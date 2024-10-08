#ifndef QCAPTUREDETAILS_H
#define QCAPTUREDETAILS_H

#include <QObject>
#include <QDateTime>

#include "qsigmftypes.h"

class QCaptureDetails : public QObject
{
    Q_OBJECT
public:
    QCaptureDetails();

    std::vector<sigmfJson_t> GetCaptureValues();
    std::vector<sigmfJson_t> GetAnnotationValues();

    // Capture
    void SetAcqScaleFactor(double);
    void SetAttenuation(double);
    void SetAcqBandwidth(double);
    void SetStartCapture(QDateTime);
    void SetStopCapture(QDateTime);
    void SetSourceFile(QString);
    void SetGain(double);

    void SetEnabled(bool);

    bool GetIsEnabled();

    // Annotations
    void SetSnr(double);
    void SetSigRefNum(QString);

public slots:

    void AddCapture();
    void AddAnnotation();

protected:

private:

    bool m_isEnabled;

    std::vector<sigmfJson_t> m_capJsonVect {
        {"capture_details:acq_scale_factor", "", true},
        {"capture_details:attenuation", "", true},
        {"capture_details:acquisition_bandwidth", "", true},
        {"capture_details:start_capture", "", true},
        {"capture_details:stop_capture", "", true},
        {"capture_details:source_file", "", true},
        {"capture_details:gain", "", false}
    };
    std::vector< std::vector<sigmfJson_t> > m_capJsonArr;

    std::vector<sigmfJson_t> m_annotJsonVect {
        {"capture_details:SNRdB", "", true},
        {"capture_details:signal_reference_number", "", true}
    };
    std::vector< std::vector<sigmfJson_t> > m_annotJsonArr;

    bool _CheckRequiredData(std::vector<sigmfJson_t>);
};

#endif // QCAPTUREDETAILS_H
