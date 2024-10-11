#include "include/qantenna.h"

QAntenna::QAntenna(QObject *parent)
    : QExtension{parent}
{
    InitializeGlobalJsonVect({
                                 {"antenna:model", "", true},
                                 {"antenna:type", "", false},
                                 {"antenna:low_frequency", "", false},
                                 {"antenna:high_frequency", "", false},
                                 {"antenna:gain", "", false},
                                 {"antenna:horizontal_gain_pattern", "", false},
                                 {"antenna:vertical_gain_pattern", "", false},
                                 {"antenna:horizontal_beam_width", "", false},
                                 {"antenna:vertical_beam_width", "", false},
                                 {"antenna:cross_polar_discrimination", "", false},
                                 {"antenna:voltage_standing_wave_ratio", "", false},
                                 {"antenna:cable_loss", "", false},
                                 {"antenna:steerable", "false", false},
                                 {"antenna:mobile", "false", false},
                                 {"antenna:hagl", "", false}
    });
    InitializeAnnotationJsonVect({
                                     {"antenna:azimuth_angle", "", false},
                                     {"antenna:elevation_angle", "", false},
                                     {"antenna:polarization", "", false}
                                 });
}

void QAntenna::SetModel(QString str)
{
    m_globalJsonVect.at(0).jsonVal = str;
}

void QAntenna::SetType(QString str)
{
    m_globalJsonVect.at(1).jsonVal = str;
}

void QAntenna::SetLowFreq(double f)
{
    m_globalJsonVect.at(2).jsonVal = QString::number(f);
}

void QAntenna::SetHighFreq(double f)
{
    m_globalJsonVect.at(3).jsonVal = QString::number(f);
}

void QAntenna::SetGain(double g)
{
    m_globalJsonVect.at(4).jsonVal = QString::number(g);
}

void QAntenna::SetHorizGain(double g)
{
    m_globalJsonVect.at(5).jsonVal = QString::number(g);
}

void QAntenna::SetVertGain(double g)
{
    m_globalJsonVect.at(6).jsonVal = QString::number(g);
}

void QAntenna::SetHorizBeamWidth(double w)
{
    m_globalJsonVect.at(7).jsonVal = QString::number(w);
}

void QAntenna::SetVertBeamWidth(double w)
{
    m_globalJsonVect.at(8).jsonVal = QString::number(w);
}

void QAntenna::SetXPolarDisc(double d)
{
    m_globalJsonVect.at(9).jsonVal = QString::number(d);
}

void QAntenna::SetVswr(double v)
{
    m_globalJsonVect.at(10).jsonVal = QString::number(v);
}

void QAntenna::SetCableLoss(double l)
{
    m_globalJsonVect.at(11).jsonVal = QString::number(l);
}

void QAntenna::SetSteerable(bool en)
{
    m_globalJsonVect.at(12).jsonVal = en ? "true" : "false";
}

void QAntenna::SetMobile(bool en)
{
    m_globalJsonVect.at(13).jsonVal = en ? "true" : "false";
}

void QAntenna::SetHagl(double h)
{
    m_globalJsonVect.at(14).jsonVal = QString::number(h);
}

void QAntenna::SetAzimuthAng(double a)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(a);
}

void QAntenna::SetElvAng(double a)
{
    m_annotJsonVect.at(1).jsonVal = QString::number(a);
}

void QAntenna::SetPolarization(QString str)
{
    m_annotJsonVect.at(2).jsonVal = str;
}
