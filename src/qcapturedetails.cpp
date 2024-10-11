#include "include/qcapturedetails.h"

/*!
 * \class QCaptureDetails
 * \since v0.0.1
 * \brief The QCaptureDetails class provides methods for configuring the Capture Details Extension
 * v1.0.0 as found at https://github.com/sigmf/SigMF/blob/main/extensions/capture_details.sigmf-ext.md
 */

/*!
 * \brief QCaptureDetails::QCaptureDetails constructs the QCaptureDetails class and initializes the
 * JSON capture and annotation vectors as found in the SigMF specification.
 * \param parent
 */
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

/*!
 * \brief QCaptureDetails::SetAcqScaleFactor sets the Acquisition Scale Factor. REQUIRED
 * \param fact (double) represents the scale factor of IQ collection from the spectrum analyzer
 * used to convert back to real power.
 */
void QCaptureDetails::SetAcqScaleFactor(double fact)
{
    m_captureJsonVect.at(0).jsonVal = QString::number(fact);
}

/*!
 * \brief QCaptureDetails::SetAttenuation sets the attenuation. REQUIRED
 * \param att (double) represents the attenuation applied to the input of the sensor.
 */
void QCaptureDetails::SetAttenuation(double att)
{
    m_captureJsonVect.at(1).jsonVal = QString::number(att);
}

/*!
 * \brief QCaptureDetails::SetAcqBandwidth sets the acquisition bandwidth. REQUIRED
 * \param bw (double) represents the bandwidth of the recording (if lower than the sample rate).
 */
void QCaptureDetails::SetAcqBandwidth(double bw)
{
    m_captureJsonVect.at(2).jsonVal = QString::number(bw);
}

/*!
 * \brief QCaptureDetails::SetStartCapture sets the start time of IQ capture. REQUIRED
 * \param dt (QDateTime) represents the time sample of IQ recording in UTC with format of
 * yyyy-mm-dd-THH:MM:SSZ
 */
void QCaptureDetails::SetStartCapture(QDateTime dt)
{
    m_captureJsonVect.at(3).jsonVal = dt.toString(Qt::ISODateWithMs);
}

/*!
 * \brief QCaptureDetails::SetStopCapture sets the stop time of the IQ capture. REQUIRED
 * \param dt (QDateTime) represents the time of the last sample of IQ recording in UTC with
 * format of yyyy-mm-dd-THH:MM:SSZ
 */
void QCaptureDetails::SetStopCapture(QDateTime dt)
{
    m_captureJsonVect.at(4).jsonVal = dt.toString(Qt::ISODateWithMs);
}

/*!
 * \brief QCaptureDetails::SetSourceFile sets the name of the source file. REQUIRED
 * \param str (QString) represents the RF IQ recording filename that was used to create the file
 * N.sigmf-data. The file N.sigmf-data may be the same or an edited version of the source_file.
 */
void QCaptureDetails::SetSourceFile(QString str)
{
    m_captureJsonVect.at(5).jsonVal = str;
}

/*!
 * \brief QCaptureDetails::SetGain sets the gain.
 * \param gain (double) represents the gain setting of the sensor for this acquisition,
 * distilled to a single number.
 */
void QCaptureDetails::SetGain(double gain)
{
    m_captureJsonVect.at(6).jsonVal = QString::number(gain);
}

/*!
 * \brief QCaptureDetails::SetSnr sets the Signal-to-Noise ratio of the capture. REQUIRED
 * \param snr (double) represents the root mean square (RMS) of the signal to noise
 * ratio (SNR). The calculation is over windows of known signal and no known signal.
 */
void QCaptureDetails::SetSnr(double snr)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(snr);
}

/*!
 * \brief QCaptureDetails::SetSigRefNum sets the signal reference number. REQUIRED
 * \param str (QString) represents the sequential reference labels for the elements that form
 * the sequence of signals identified in a SigMF dataset file. The format of the string is the
 * filename followed by an index that increases with each decoded signal. An example is a recording
 * dataset file named N.sigmf-data would have signal numbers starting with N-1, N-1, N-3, ...
 */
void QCaptureDetails::SetSigRefNum(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}
