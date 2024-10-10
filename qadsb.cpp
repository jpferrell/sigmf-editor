#include "qadsb.h"

QAdsb::QAdsb(QObject *parent)
    : QExtension{parent}
{
    InitializeAnnotationJsonVect({
                                     {"adsb:downlink_format", "", true},
                                     {"adsb:message_type", "", true},
                                     {"adsb:ICA_address", "", true},
                                     {"adsb:binary", "", true}
                                 });
}

void QAdsb::SetDownlinkFrmt(int num)
{
    m_annotJsonVect.at(0).jsonVal = num == 0 ? "11" : "17";
}

void QAdsb::SetMessageType(int num)
{
    m_annotJsonVect.at(1).jsonVal = QString::number(num);
}

void QAdsb::SetIcaAddr(double d)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(d);
}

void QAdsb::SetBinary(QString str)
{
    m_annotJsonVect.at(3).jsonVal = str;
}
