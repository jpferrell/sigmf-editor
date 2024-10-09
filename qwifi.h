#ifndef QWIFI_H
#define QWIFI_H

#include <QObject>
#include <QDebug>

#include "qsigmftypes.h"

class QWifi : public QObject
{
    Q_OBJECT
public:
    explicit QWifi(QObject *parent = nullptr);

    std::vector<sigmfJson_t> GetAnnotationValues();

    void SetEnabled(bool);
    bool GetIsEnabled();

    void SetStandard(QString);
    void SetFrameTypePhy(QString);
    void SetChannel(int);
    void SetStartTime(double);
    void SetStopTime(double);
    void SetFrameDuration(double);
    void SetMcs(int);
    void SetMacFrameType(QString);
    void SetMacTxAddr(QString);
    void SetMacRxAddr(QString);
    void SetTxManf(QString);
    void SetMacFrame(QString);
    void SetCrc(QString);
    void SetStartPkt(double);
    void SetEndPkt(double);
    void SetNumSampsPkt(double);

signals:

public slots:

protected:

private:

    bool m_isEnabled;

    std::vector<sigmfJson_t> m_annotJsonVect {
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
        {"wifi:number_of_samples_in_packet", "", true},
    };
    std::vector< std::vector<sigmfJson_t> > m_annotJsonArr;

    bool _CheckRequiredData(std::vector<sigmfJson_t>);

};

#endif // QWIFI_H
