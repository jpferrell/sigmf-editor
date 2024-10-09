#ifndef QANTENNA_H
#define QANTENNA_H

#include "qextension.h"
#include <QObject>

class QAntenna : public QExtension
{
    Q_OBJECT
public:
    explicit QAntenna(QObject *parent = nullptr);

    void SetModel(QString str);
    void SetType(QString str);
    void SetLowFreq(double f);
    void SetHighFreq(double f);
    void SetGain(double g);
    void SetHorizGain(double g);
    void SetVertGain(double g);
    void SetHorizBeamWidth(double w);
    void SetVertBeamWidth(double w);
    void SetXPolarDisc(double d);
    void SetVswr(double v);
    void SetCableLoss(double l);
    void SetSteerable(bool en);
    void SetMobile(bool en);
    void SetHagl(double h);

    void SetAzimuthAng(double a);
    void SetElvAng(double a);
    void SetPolarization(QString str);
};

#endif // QANTENNA_H
