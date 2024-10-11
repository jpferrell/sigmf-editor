#ifndef QADSB_H
#define QADSB_H

#include <QDebug>

#include "include/qextension.h"

class QAdsb : public QExtension
{
    Q_OBJECT
public:
    explicit QAdsb(QObject *parent = nullptr);

    void SetDownlinkFrmt(int);
    void SetMessageType(int);
    void SetIcaAddr(double);
    void SetBinary(QString);

signals:

public slots:

protected:

private:
};

#endif // QADSB_H
