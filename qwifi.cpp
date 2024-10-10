#include "qwifi.h"

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
}

void QWifi::SetStandard(QString str)
{
    m_annotJsonVect.at(0).jsonVal = str;
}

void QWifi::SetFrameTypePhy(QString str)
{
    m_annotJsonVect.at(1).jsonVal = str;
}

void QWifi::SetChannel(int c)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(c);
}

void QWifi::SetStartTime(double t)
{
    m_annotJsonVect.at(3).jsonVal = QString::number(t);
}

void QWifi::SetStopTime(double t)
{
    m_annotJsonVect.at(4).jsonVal = QString::number(t);
}

void QWifi::SetFrameDuration(double d)
{
    m_annotJsonVect.at(5).jsonVal = QString::number(d);
}

void QWifi::SetMcs(int m)
{
    m_annotJsonVect.at(6).jsonVal = QString::number(m);
}

void QWifi::SetMacFrameType(QString str)
{
    m_annotJsonVect.at(7).jsonVal = str;
}

void QWifi::SetMacTxAddr(QString str)
{
    m_annotJsonVect.at(8).jsonVal = str;
}

void QWifi::SetMacRxAddr(QString str)
{
    m_annotJsonVect.at(9).jsonVal = str;
}

void QWifi::SetTxManf(QString str)
{
    m_annotJsonVect.at(10).jsonVal = str;
}

void QWifi::SetMacFrame(QString str)
{
    m_annotJsonVect.at(11).jsonVal = str;
}

void QWifi::SetCrc(QString str)
{
    m_annotJsonVect.at(12).jsonVal = str;
}

void QWifi::SetStartPkt(double s)
{
    m_annotJsonVect.at(13).jsonVal = QString::number(s);
}

void QWifi::SetEndPkt(double s)
{
    m_annotJsonVect.at(14).jsonVal = QString::number(s);
}

void QWifi::SetNumSampsPkt(double s)
{
    m_annotJsonVect.at(15).jsonVal = QString::number(s);
}
