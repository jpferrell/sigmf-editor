#include "include/qwifi.h"

/*!
 * \class QWifi
 * \since v0.0.1
 *
 * \brief The QWifi class holds the data for the SigMF Wifi Extension as seen in
 * https://github.com/sigmf/community-extensions/blob/main/wifi/wifi.sigmf-ext.md
 */

/*!
 * \brief QWifi::QWifi constructs the QWifi class with JSON keys as shown in specification.
 * \param parent (QObject *)
 */
QWifi::QWifi(QObject *parent)
    : QExtension{parent}
{
    InitializeAnnotationJsonVect({
                                     {"wifi:standard", "", true},
                                     {"wifi:frame_type_phy", "", true},
                                     {"wifi:channel", "", true},
                                     {"wifi:start_time_s", "", true},
                                     {"wifi:stop_time_s", "", true},
                                     {"wifi:frame_duration_s", "", true},
                                     {"wifi:MCS", "", true},
                                     {"wifi:MAC_Frame_type", "", true},
                                     {"wifi:MAC_ta", "", true},
                                     {"wifi:MAC_ra", "", true},
                                     {"wifi:manufacturer_ta", "", true},
                                     {"wifi:MAC_frame", "", true},
                                     {"wifi:CRC", "", true},
                                     {"wifi:start_of_packet", "", true},
                                     {"wifi:stop_of_packet", "", true},
                                     {"wifi:number_of_samples_in_packet", "", true}
                                });
    SetGlobalExtensionObject("wifi", "1.0.0", false);
}

sigmfVector_t QWifi::GetAnnotationValues()
{
    sigmfVector_t retVect = QSigMfBase::GetAnnotationValues();
    QString opt = GetExtensionOptional() ? "true" : "false";
    emit extensionEnabled(GetExtensionName(), GetExtensionVersion(), opt);

    return retVect;
}

/*!
 * \brief QWifi::SetStandard sets the standard. REQUIRED
 * \param str (QString) represents the wireless standard of captured signal, e.g. 802.11a/g
 */
void QWifi::SetStandard(QString str)
{
    m_annotJsonVect.at(0).jsonVal = str;
}

/*!
 * \brief QWifi::SetFrameTypePhy sets the physical frame type. REQUIRED
 * \param str (QString) represents the physical layer specification, e.g. non-high throughput
 * or very-high throughput.
 */
void QWifi::SetFrameTypePhy(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}

/*!
 * \brief QWifi::SetChannel sets the channel. REQUIRED
 * \param c (int) represents the Wi-Fi channel of the captured signal.
 */
void QWifi::SetChannel(int c)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(c);
}

/*!
 * \brief QWifi::SetStartTime sets the start time of the burst in seconds. REQUIRED
 * \param t (double) represents the start time of the RF burst (relative time to start time of
 * main capture file).
 */
void QWifi::SetStartTime(double t)
{
    m_annotJsonVect.at(3).jsonVal = QString::number(t);
}

/*!
 * \brief QWifi::SetStopTime sets the stop time of the burst in seconds. REQUIRED
 * \param t (double) represents the stop time of RF burst (relative time to start time of main
 * caputre file).
 */
void QWifi::SetStopTime(double t)
{
    m_annotJsonVect.at(4).jsonVal = QString::number(t);
}

/*!
 * \brief QWifi::SetFrameDuration sets duration of burst in seconds. REQUIRED
 * \param d (double) represents the duration of the burst (stop_time_s - start_time_s).
 */
void QWifi::SetFrameDuration(double d)
{
    m_annotJsonVect.at(5).jsonVal = QString::number(d);
}

/*!
 * \brief QWifi::SetMcs sets modulation and coding scheme (MCS). REQUIRED
 * \param m (int) represents the Wi-Fi signal Modulation and Coding Scheme (MCS).
 */
void QWifi::SetMcs(int m)
{
    m_annotJsonVect.at(6).jsonVal = QString::number(m);
}

/*!
 * \brief QWifi::SetMacFrameType sets the MAC frame type. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame type.
 */
void QWifi::SetMacFrameType(QString str)
{
    m_annotJsonVect.at(7).jsonVal = str;
}

/*!
 * \brief QWifi::SetMacTxAddr sets the transmitter MAC address. REQUIRED
 * \param str (QString) represents the MAC address of the Wi-Fi transmitter.
 */
void QWifi::SetMacTxAddr(QString str)
{
    m_annotJsonVect.at(8).jsonVal = str;
}

/*!
 * \brief QWifi::SetMacTxAddr sets the receiver MAC address. REQUIRED
 * \param str (QString) represents the MAC address of the Wi-Fi receiver.
 */
void QWifi::SetMacRxAddr(QString str)
{
    m_annotJsonVect.at(9).jsonVal = str;
}

/*!
 * \brief QWifi::SetTxManf sets the transmitter manufacturer. REQUIRED
 * \param str (QString) represents the manufacturer of the Wi-Fi transmitter.
 */
void QWifi::SetTxManf(QString str)
{
    m_annotJsonVect.at(10).jsonVal = str;
}

/*!
 * \brief QWifi::SetMacFrame sets the MAC frame data without CRC. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame data without the CRC.
 */
void QWifi::SetMacFrame(QString str)
{
    m_annotJsonVect.at(11).jsonVal = str;
}

/*!
 * \brief QWifi::SetCrc sets the CRC. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame CRC.
 */
void QWifi::SetCrc(QString str)
{
    m_annotJsonVect.at(12).jsonVal = str;
}

/*!
 * \brief QWifi::SetStartPkt sets the starting sample of burst. REQUIRED
 * \param s (double) represents the starting sample of the captured Wi-Fi burst.
 */
void QWifi::SetStartPkt(double s)
{
    m_annotJsonVect.at(13).jsonVal = QString::number(s);
}

/*!
 * \brief QWifi::SetEndPkt sets the stopping sample of burst. REQUIRED
 * \param s (double) represents the stopping sample of captured Wi-Fi burst.
 */
void QWifi::SetEndPkt(double s)
{
    m_annotJsonVect.at(14).jsonVal = QString::number(s);
}

/*!
 * \brief QWifi::SetNumSampsPkt sets the number of samples in burst. REQUIRED
 * \param s (double) represents the number of downsampled IQ samples in Wi-Fi burst.
 */
void QWifi::SetNumSampsPkt(double s)
{
    m_annotJsonVect.at(15).jsonVal = QString::number(s);
}
