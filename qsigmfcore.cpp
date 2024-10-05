#include "qsigmfcore.h"

QSigMfCore::QSigMfCore(QObject *parent)
    : QObject{parent}
    , m_globalVars()
{
}

QJsonObject QSigMfCore::GenerateJson()
{
    QJsonObject retObj;
    _UpdateDataType();
    bool isValid = _CheckRequiredData();
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_jsonVect.begin(); it != m_jsonVect.end(); it++) {
            if (it->isRequired) {
                retObj.insert(it->jsonKey, it->jsonVal);
            } else if (it->jsonVal.compare("")) {
                // Not an empty value
                retObj.insert(it->jsonKey, it->jsonVal);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retObj;
}

void QSigMfCore::SetSampleRate(double sr)
{
    m_jsonVect.at(0).jsonVal = QString::number(sr);
}

void QSigMfCore::SetAuthor(QString auth)
{
    m_jsonVect.at(1).jsonVal = auth;
}

void QSigMfCore::SetMetaDoi(QString doi)
{
    m_jsonVect.at(13).jsonVal = doi;
}

void QSigMfCore::SetDataDoi(QString doi)
{
    m_jsonVect.at(12).jsonVal = doi;
}

void QSigMfCore::SetDescription(QString desc)
{
    m_jsonVect.at(2).jsonVal = desc;
}

void QSigMfCore::SetLicense(QString l)
{
    m_jsonVect.at(3).jsonVal = l;
}

void QSigMfCore::SetHardware(QString hw)
{
    m_jsonVect.at(8).jsonVal = hw;
}

void QSigMfCore::SetMetadataOnly(bool isMetaOnly)
{
    m_jsonVect.at(4).jsonVal = isMetaOnly ? QString("true") : QString("false");
}

void QSigMfCore::SetNumberChannels(int num)
{
    m_jsonVect.at(5).jsonVal = QString::number(num);
}

void QSigMfCore::SetOffset(int offset)
{
    m_jsonVect.at(6).jsonVal = QString::number(offset);
}

void QSigMfCore::SetRecorder(QString rec)
{
    m_jsonVect.at(14).jsonVal = rec;
}

void QSigMfCore::SetTrailingBytes(int num)
{
    m_jsonVect.at(16).jsonVal = QString::number(num);
}

void QSigMfCore::SetVersion(QString v)
{
    m_jsonVect.at(9).jsonVal = v;
}

void QSigMfCore::SetDataset(QString str)
{
    m_jsonVect.at(11).jsonVal = str;
}

void QSigMfCore::SetSha512(QString)
{

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
    bool isCplx = str.compare("Complex") ? true : false;
    m_globalVars.SetComplex(isCplx);
}

void QSigMfCore::SetDataFormat(QString str)
{
    m_globalVars.SetDataFormat(str+"_");
}

void QSigMfCore::SetEndianness(QString str)
{
    QString end = str.compare("Big Endian") ? "le" : "be";
    m_globalVars.SetEndianness(end);
}

bool QSigMfCore::_CheckRequiredData()
{
    bool isCorrect = true;
    for (auto it = m_jsonVect.begin(); it != m_jsonVect.end(); it++) {
        if (it->isRequired && !it->jsonVal.compare("")) {
            // If the element is required but is empty, the spec is not fulfilled
            qDebug() << "value is not defined: " << it->jsonKey;
            qDebug() << "Value of " << it->jsonVal;
            isCorrect = false;
        }
    }
    return isCorrect;
}

void QSigMfCore::_UpdateDataType()
{
    m_jsonVect.at(7).jsonVal = m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness();
    qDebug() << m_jsonVect.at(7).jsonKey << ": " << m_jsonVect.at(7).jsonVal;
}
