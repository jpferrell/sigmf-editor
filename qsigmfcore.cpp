#include "qsigmfcore.h"

QSigMfCore::QSigMfCore(QObject *parent)
    : QSigMfBase{parent}
    , m_globalVars()
{
    InitializeGlobalJsonVect({
                                 {"core:sample_rate", "", false},
                                 {"core:author", "", false},
                                 {"core:description", "", false},
                                 {"core:license", "", false},
                                 {"core:metadata_only", "", false},
                                 {"core:number_channels", "", false},
                                 {"core:offset", "", false},
                                 {"core:datatype", "", true},
                                 {"core:hw", "", false},
                                 {"core:version", "", true},
                                 {"core:collection", "", false},
                                 {"core:dataset", "", false},
                                 {"core:data_doi", "", false},
                                 {"core:meta_doi", "", false},
                                 {"core:recorder", "", false},
                                 {"core:sha512", "", false},
                                 {"core:trailing_bytes", "", false},
                                 {"core:geolocation", "", false},
                                 {"core:extensions", "", false}
                             });
    InitializeCaptureJsonVect({
                                  {"core:sample_start", "", true},
                                  {"core:datetime", "", false},
                                  {"core:frequency", "", false},
                                  {"core:global_index", "", false},
                                  {"core:header_bytes", "", false}
                              });
    InitializeAnnotationJsonVect({
                                     {"core:sample_start", "", true},
                                     {"core:sample_count", "", false},
                                     {"core:freq_lower_edge", "", false},
                                     {"core:freq_upper_edge", "", false},
                                     {"core:label", "", false},
                                     {"core:comment", "", false},
                                     {"core:generator", "", false},
                                     {"core:uuid", "", false}
                                 });
}

void QSigMfCore::SetSampleRate(double sr)
{
    m_globalJsonVect.at(0).jsonVal = QString::number(sr);
}

void QSigMfCore::SetAuthor(QString auth)
{
    m_globalJsonVect.at(1).jsonVal = auth;
}

void QSigMfCore::SetMetaDoi(QString doi)
{
    m_globalJsonVect.at(13).jsonVal = doi;
}

void QSigMfCore::SetDataDoi(QString doi)
{
    m_globalJsonVect.at(12).jsonVal = doi;
}

void QSigMfCore::SetDescription(QString desc)
{
    m_globalJsonVect.at(2).jsonVal = desc;
}

void QSigMfCore::SetLicense(QString l)
{
    m_globalJsonVect.at(3).jsonVal = l;
}

void QSigMfCore::SetHardware(QString hw)
{
    m_globalJsonVect.at(8).jsonVal = hw;
}

void QSigMfCore::SetMetadataOnly(bool isMetaOnly)
{
    m_globalJsonVect.at(4).jsonVal = isMetaOnly ? QString("true") : QString("false");
}

void QSigMfCore::SetNumberChannels(int num)
{
    m_globalJsonVect.at(5).jsonVal = QString::number(num);
}

void QSigMfCore::SetOffset(int offset)
{
    m_globalJsonVect.at(6).jsonVal = QString::number(offset);
}

void QSigMfCore::SetRecorder(QString rec)
{
    m_globalJsonVect.at(14).jsonVal = rec;
}

void QSigMfCore::SetTrailingBytes(int num)
{
    m_globalJsonVect.at(16).jsonVal = QString::number(num);
}

void QSigMfCore::SetVersion(QString v)
{
    m_globalJsonVect.at(9).jsonVal = v;
}

void QSigMfCore::SetDataset(QString str)
{
    m_globalJsonVect.at(11).jsonVal = str;
}

void QSigMfCore::SetSha512(QString str)
{
    m_globalJsonVect.at(15).jsonVal = str;
}

void QSigMfCore::SetGeoType(QString gt)
{
    m_globalVars.SetGeoType(gt);
}

void QSigMfCore::SetLat(double lat)
{
    m_globalVars.SetLat(lat);
}

void QSigMfCore::SetLon(double lon)
{
    m_globalVars.SetLon(lon);
}

void QSigMfCore::SetElevation(double elv)
{
    m_globalVars.SetElevation(elv);
}

void QSigMfCore::SetComplex(const QString &str)
{
    bool isCplx = str.compare("Complex") ? false : true;
    m_globalVars.SetComplex(isCplx);
    _UpdateDataType();
}

void QSigMfCore::SetDataFormat(QString str)
{
    m_globalVars.SetDataFormat(str+"_");
    _UpdateDataType();
}

void QSigMfCore::SetEndianness(QString str)
{
    QString end = str.compare("Big Endian") ? "le" : "be";
    m_globalVars.SetEndianness(end);
    _UpdateDataType();
}

void QSigMfCore::SetSampleStart(int val)
{
    m_captureJsonVect.at(0).jsonVal = QString::number(val);
}

void QSigMfCore::SetDatetime(QDateTime dt)
{
    m_captureJsonVect.at(1).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QSigMfCore::SetFrequency(double val)
{
    m_captureJsonVect.at(2).jsonVal = QString::number(val);
}

void QSigMfCore::SetGlobalIndex(int val)
{
    m_captureJsonVect.at(3).jsonVal = QString::number(val);
}

void QSigMfCore::SetHeaderBytes(int val)
{
    m_captureJsonVect.at(4).jsonVal = QString::number(val);
}

void QSigMfCore::SetDatetimeEnabled(bool)
{
}

void QSigMfCore::SetAnnotSampleStart(int sr)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(sr);
}

void QSigMfCore::SetSampleCount(int sc)
{
    m_annotJsonVect.at(1).jsonVal = QString::number(sc);
}

void QSigMfCore::SetFrequencyLower(double freq)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(freq);
}

void QSigMfCore::SetFrequencyHigher(double freq)
{
    m_annotJsonVect.at(3).jsonVal = QString::number(freq);
}

void QSigMfCore::SetLabel(QString str)
{
    m_annotJsonVect.at(4).jsonVal = str;
}

void QSigMfCore::SetComment(QString str)
{
    m_annotJsonVect.at(5).jsonVal = str;
}

void QSigMfCore::SetGenerator(QString str)
{
    m_annotJsonVect.at(6).jsonVal = str;
}

void QSigMfCore::SetUuid(QString str)
{
    m_annotJsonVect.at(7).jsonVal = str;
}

void QSigMfCore::_UpdateDataType()
{
    m_globalJsonVect.at(7).jsonVal = m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness();
}
