#include "qsigmfcore.h"

QSigMfCore::QSigMfCore(QObject *parent)
    : QObject{parent}
{}

QJsonObject QSigMfCore::GenerateJson()
{
    bool isValid = _CheckRequiredData();
    QJsonObject retObj;

}

void QSigMfCore::SetSampleRate(double sr)
{
    globalVars.SetSampleRate(sr);
}

void QSigMfCore::SetAuthor(QString auth)
{
    globalVars.SetAuthor(auth);
}

void QSigMfCore::SetMetaDoi(QString doi)
{
    globalVars.SetMetaDoi(doi);
}

void QSigMfCore::SetDataDoi(QString doi)
{
    globalVars.SetDataDoi(doi);
}

void QSigMfCore::SetDescription(QString desc)
{
    globalVars.SetDescription(desc);
}

void QSigMfCore::SetLicense(QString l)
{
    globalVars.SetLicense(l);
}

void QSigMfCore::SetMetadataOnly(bool isMetaOnly)
{
    globalVars.SetMetadataOnly(isMetaOnly);
}

void QSigMfCore::SetNumberChannels(int num)
{
    globalVars.SetNumberChannels(num);
}

void QSigMfCore::SetOffset(int offset)
{
    globalVars.SetOffset(offset);
}

void QSigMfCore::SetRecorder(QString rec)
{
    globalVars.SetRecorder(rec);
}

void QSigMfCore::SetTrailingBytes(int num)
{
    globalVars.SetTrailingBytes(num);
}

void QSigMfCore::SetVersion(QString v)
{
    globalVars.SetVersion(v);
}

void QSigMfCore::SetGeoType(QString gt)
{
    globalVars.SetGeoType(gt);
}

void QSigMfCore::SetLat(double lat)
{
    globalVars.SetLat(lat);
}

void QSigMfCore::SetLon(double lon)
{
    globalVars.SetLon(lon);
}

void QSigMfCore::SetElevation(double elv)
{
    globalVars.SetElevation(elv);
}

bool QSigMfCore::_CheckRequiredData()
{
    return false;
}
