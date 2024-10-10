#ifndef QWIFI_H
#define QWIFI_H

#include <QObject>
#include <QDebug>

#include "qextension.h"

class QWifi : public QExtension
{
    Q_OBJECT
public:
    explicit QWifi(QObject *parent = nullptr);

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

};

#endif // QWIFI_H
