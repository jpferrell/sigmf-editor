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
    : QExtension{
        {},
        {},
        {
            "standard",
            "frame_type_phy",
            "channel",
            "start_time_s",
            "stop_time_s",
            "frame_duration_s",
            "MCS",
            "MAC_Frame_type",
            "MAC_ta",
            "MAC_ra",
            "manufacturer_ta",
            "MAC_frame",
            "CRC",
            "start_of_packet",
            "stop_of_packet",
            "number_of_samples_in_packet"
        },
        parent
    }
{
    SetGlobalExtensionObject("wifi", "1.0.0", false);
}

/*
sigmfVector_t QWifi::GetAnnotationValues()
{
    sigmfVector_t retVect = QSigMfBase::GetAnnotationValues();
    QString opt = GetExtensionOptional() ? "true" : "false";
    emit extensionEnabled(GetExtensionName(), GetExtensionVersion(), opt);

    return retVect;
}
*/

/*!
 * \brief QWifi::SetStandard sets the standard. REQUIRED
 * \param str (QString) represents the wireless standard of captured signal, e.g. 802.11a/g
 */
void QWifi::SetStandard(QString str)
{
    m_annotJsonMap.insert_or_assign("standard", QJsonObject{{"wifi:standard", str}});
}

/*!
 * \brief QWifi::SetFrameTypePhy sets the physical frame type. REQUIRED
 * \param str (QString) represents the physical layer specification, e.g. non-high throughput
 * or very-high throughput.
 */
void QWifi::SetFrameTypePhy(QString str)
{
    m_annotJsonMap.insert_or_assign("standard", QJsonObject{{"wifi:frame_type_phy", str}});
}

/*!
 * \brief QWifi::SetChannel sets the channel. REQUIRED
 * \param c (int) represents the Wi-Fi channel of the captured signal.
 */
void QWifi::SetChannel(int c)
{
    m_annotJsonMap.insert_or_assign("channel", QJsonObject{{"wifi:channel", c}});
}

/*!
 * \brief QWifi::SetStartTime sets the start time of the burst in seconds. REQUIRED
 * \param t (double) represents the start time of the RF burst (relative time to start time of
 * main capture file).
 */
void QWifi::SetStartTime(double t)
{
    m_annotJsonMap.insert_or_assign("start_time_s", QJsonObject{{"wifi:start_time_s", t}});
}

/*!
 * \brief QWifi::SetStopTime sets the stop time of the burst in seconds. REQUIRED
 * \param t (double) represents the stop time of RF burst (relative time to start time of main
 * caputre file).
 */
void QWifi::SetStopTime(double t)
{
    m_annotJsonMap.insert_or_assign("stop_time_s", QJsonObject{{"wifi:stop_time_s", t}});
}

/*!
 * \brief QWifi::SetFrameDuration sets duration of burst in seconds. REQUIRED
 * \param d (double) represents the duration of the burst (stop_time_s - start_time_s).
 */
void QWifi::SetFrameDuration(double d)
{
    m_annotJsonMap.insert_or_assign("frame_duration_s", QJsonObject{{"wifi:frame_duration_s", d}});
}

/*!
 * \brief QWifi::SetMcs sets modulation and coding scheme (MCS). REQUIRED
 * \param m (int) represents the Wi-Fi signal Modulation and Coding Scheme (MCS).
 */
void QWifi::SetMcs(int m)
{
    m_annotJsonMap.insert_or_assign("MCS", QJsonObject{{"wifi:MCS", m}});
}

/*!
 * \brief QWifi::SetMacFrameType sets the MAC frame type. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame type.
 */
void QWifi::SetMacFrameType(QString str)
{
    m_annotJsonMap.insert_or_assign("MAC_frame_type", QJsonObject{{"wifi:MAC_frame_type", str}});
}

/*!
 * \brief QWifi::SetMacTxAddr sets the transmitter MAC address. REQUIRED
 * \param str (QString) represents the MAC address of the Wi-Fi transmitter.
 */
void QWifi::SetMacTxAddr(QString str)
{
    m_annotJsonMap.insert_or_assign("MAC_ta", QJsonObject{{"wifi:MAC_ta", str}});
}

/*!
 * \brief QWifi::SetMacTxAddr sets the receiver MAC address. REQUIRED
 * \param str (QString) represents the MAC address of the Wi-Fi receiver.
 */
void QWifi::SetMacRxAddr(QString str)
{
    m_annotJsonMap.insert_or_assign("MAC_ra", QJsonObject{{"wifi:MAC_ra", str}});
}

/*!
 * \brief QWifi::SetTxManf sets the transmitter manufacturer. REQUIRED
 * \param str (QString) represents the manufacturer of the Wi-Fi transmitter.
 */
void QWifi::SetTxManf(QString str)
{
    m_annotJsonMap.insert_or_assign("manufacturer_ta", QJsonObject{{"wifi:manufacturer_ta", str}});
}

/*!
 * \brief QWifi::SetMacFrame sets the MAC frame data without CRC. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame data without the CRC.
 */
void QWifi::SetMacFrame(QString str)
{
    m_annotJsonMap.insert_or_assign("MAC_frame", QJsonObject{{"wifi:MAC_frame", str}});
}

/*!
 * \brief QWifi::SetCrc sets the CRC. REQUIRED
 * \param str (QString) represents the Wi-Fi MAC frame CRC.
 */
void QWifi::SetCrc(QString str)
{
    m_annotJsonMap.insert_or_assign("CRC", QJsonObject{{"wifi:CRC", str}});
}

/*!
 * \brief QWifi::SetStartPkt sets the starting sample of burst. REQUIRED
 * \param s (double) represents the starting sample of the captured Wi-Fi burst.
 */
void QWifi::SetStartPkt(double s)
{
    m_annotJsonMap.insert_or_assign("start_of_packet", QJsonObject{{"wifi:start_of_packet", s}});
}

/*!
 * \brief QWifi::SetEndPkt sets the stopping sample of burst. REQUIRED
 * \param s (double) represents the stopping sample of captured Wi-Fi burst.
 */
void QWifi::SetEndPkt(double s)
{
    m_annotJsonMap.insert_or_assign("stop_of_packet", QJsonObject{{"wifi:stop_of_packet", s}});
}

/*!
 * \brief QWifi::SetNumSampsPkt sets the number of samples in burst. REQUIRED
 * \param s (double) represents the number of downsampled IQ samples in Wi-Fi burst.
 */
void QWifi::SetNumSampsPkt(double s)
{
    m_annotJsonMap.insert_or_assign("number_of_samples_in_packet", QJsonObject{{"wifi:number_of_samples_in_packet", s}});
}
