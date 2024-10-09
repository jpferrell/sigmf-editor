#ifndef QADSB_H
#define QADSB_H

#include <QObject>
#include <QDebug>

#include "qsigmftypes.h"

class QAdsb : public QObject
{
    Q_OBJECT
public:
    explicit QAdsb(QObject *parent = nullptr);

    std::vector<sigmfJson_t> GetAnnotationValues();

    void SetEnabled(bool);

    void SetDownlinkFrmt(int);
    void SetMessageType(int);
    void SetIcaAddr(double);
    void SetBinary(QString);

    bool GetIsEnabled();

signals:

public slots:

protected:

private:

    bool m_isEnabled;

    std::vector<sigmfJson_t> m_annotJsonVect {
        {"adsb:downlink_format", "", true},
        {"adsb:message_type", "", true},
        {"adsb:ICA_address", "", true},
        {"adsb:binary", "", true}
    };
    std::vector< std::vector<sigmfJson_t> > m_annotJsonArr;

    bool _CheckRequiredData(std::vector<sigmfJson_t>);
};

#endif // QADSB_H
