#include "include/qantenna.h"

QAntenna::QAntenna(QObject *parent)
    : QExtension{{"model"},{},{},parent}
{
    SetGlobalExtensionObject("antenna", "1.0.0", false);
}

void QAntenna::SetModel(QString str)
{
    m_globalJsonMap.insert_or_assign("model", QJsonObject{{"antenna:model", str}});
}

void QAntenna::SetType(QString str)
{
    m_globalJsonMap.insert_or_assign("type", QJsonObject{{"antenna:type", str}});
}

void QAntenna::SetLowFreq(double f)
{
    m_globalJsonMap.insert_or_assign("low_frequency", QJsonObject{{"antenna:low_frequency", f}});
}

void QAntenna::SetHighFreq(double f)
{
    m_globalJsonMap.insert_or_assign("high_frequency", QJsonObject{{"antenna:high_frequency", f}});
}

void QAntenna::SetGain(double g)
{
    m_globalJsonMap.insert_or_assign("gain", QJsonObject{{"antenna:gain", g}});
}

void QAntenna::SetHorizGain(double g)
{
    m_globalJsonMap.insert_or_assign("horizontal_gain_pattern", QJsonObject{{"antenna:horizontal_gain_pattern", g}});
}

void QAntenna::SetVertGain(double g)
{
    m_globalJsonMap.insert_or_assign("vertical_gain_pattern", QJsonObject{{"antenna:vertical_gain_pattern", g}});
}

void QAntenna::SetHorizBeamWidth(double w)
{
    m_globalJsonMap.insert_or_assign("horizontal_beam_width", QJsonObject{{"antenna:horizontal_beam_width", w}});
}

void QAntenna::SetVertBeamWidth(double w)
{
    m_globalJsonMap.insert_or_assign("vertical_beam_width", QJsonObject{{"antenna:vertical_beam_width", w}});
}

void QAntenna::SetXPolarDisc(double d)
{
    m_globalJsonMap.insert_or_assign("cross_polar_discrimination", QJsonObject{{"antenna:cross_polar_discrimination", d}});
}

void QAntenna::SetVswr(double v)
{
    m_globalJsonMap.insert_or_assign("voltage_standing_wave_ratio", QJsonObject{{"antenna:voltage_standing_wave_ratio", v}});
}

void QAntenna::SetCableLoss(double l)
{
    m_globalJsonMap.insert_or_assign("cable_loss", QJsonObject{{"antenna:cable_loss", l}});
}

void QAntenna::SetSteerable(bool en)
{
    QString valStr = en ? "true" : "false";
    m_globalJsonMap.insert_or_assign("steerable", QJsonObject{{"antenna:steerable", valStr}});
}

void QAntenna::SetMobile(bool en)
{
    QString valStr = en ? "true" : "false";
    m_globalJsonMap.insert_or_assign("mobile", QJsonObject{{"antenna:mobile", valStr}});
}

void QAntenna::SetHagl(double h)
{
    m_globalJsonMap.insert_or_assign("hagl", QJsonObject{{"antenna:hagl", h}});
}

void QAntenna::SetAzimuthAng(double a)
{
    m_annotJsonMap.insert_or_assign("azimuth_angle", QJsonObject{{"antenna:azimuth_angle", a}});
}

void QAntenna::SetElvAng(double a)
{
    m_annotJsonMap.insert_or_assign("elevation_angle", QJsonObject{{"antenna:elevation_angle", a}});
}

void QAntenna::SetPolarization(QString str)
{
    m_annotJsonMap.insert_or_assign("polarization", QJsonObject{{"antenna:polarization", str}});
}
