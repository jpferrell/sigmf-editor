#include "include/qadsb.h"

/*!
 * \class QAdsb
 * \since v0.0.1
 *
 * \brief The QAdsb class represents the ADS-B SigMF Extension v1.0.0 as found at
 * https://github.com/sigmf/community-extensions/blob/main/adsb/adsb.sigmf-ext.md
 */

/*!
 * \brief QAdsb::QAdsb constructs the QAdsb class and initializes the annotation JSON
 * vector with the keys found in the specification.
 * \param parent (QObject *)
 */
QAdsb::QAdsb(QObject *parent)
    : QExtension{
        {},
        {},
        {"downlink_format", "message_type", "ICA_address", "binary"},
        parent}
{
    // check these values
    SetGlobalExtensionObject("adsb", "v1.0.0", true);
}

/*!
 * \brief QAdsb::SetDownlinkFrmt sets the Downlink Format. REQUIRED
 * \param num (int) indicates if an ADS-B signal is a Mode S Short (11) or a Mode S
 * Extended (17) signal.
 */
void QAdsb::SetDownlinkFrmt(int num)
{
    QString numStr = num == 0 ? "11" : "17";
    m_annotJsonMap.insert_or_assign("downlink_format", QJsonObject{{"adsb:downlink_format", numStr}});
}

/*!
 * \brief QAdsb::SetMessageType sets the message type. REQUIRED
 * \param num (int) indicates the type of data in a Mode S Extended signal. The message
 * type code range is from 0 to 31. The type of messages are aircraft identification (1-4),
 * surface position (5-8), airborne position with barometric (9-18), airborne velocities (19),
 * airborne position with GNSS (20-22), testing (23), reserved (24-27, 30), Emergency/Airborne
 * Collision Avoidance System (ACAS) status (28), trajectory change (29), and aircraft
 * operational status (31). A signal with a Mode S Short downlink format does not contain a
 * message and is represented by a 0.
 */
void QAdsb::SetMessageType(int num)
{
    m_annotJsonMap.insert_or_assign("message_type", QJsonObject{{"adsb:message_type", num}});
}

/*!
 * \brief QAdsb::SetIcaAddr sets the ICAO address.
 * \param d (double) represents the International Civil Aviation Organization (ICAO) address
 * of the ADS-B signal.
 */
void QAdsb::SetIcaAddr(double d)
{
    m_annotJsonMap.insert_or_assign("ICA_address", QJsonObject{{"adsb:ICA_address", d}});
}

/*!
 * \brief QAdsb::SetBinary sets the binary data.
 * \param str (QString) represents the binary data of the signal, either 56 bits (Mode S
 * Short) or 112 bits (Mode S Extended).
 */
void QAdsb::SetBinary(QString str)
{
    m_annotJsonMap.insert_or_assign("binary", QJsonObject{{"adsb:binary", str}});
}
