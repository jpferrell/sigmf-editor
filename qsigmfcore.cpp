#include "qsigmfcore.h"

QSigMfCore::QSigMfCore(QObject *parent)
    : QObject{parent}
    , m_globalVars()
{
}

/*
QJsonObject QSigMfCore::GenerateGlobalJson()
{
    QJsonObject retObj;
    _UpdateDataType();
    bool isValid = _CheckRequiredData();
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_globalJsonVect.begin(); it != m_globalJsonVect.end(); it++) {
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
*/

std::vector<sigmfJson_t> QSigMfCore::GetGlobalValues()
{
    std::vector<sigmfJson_t> retVect;
    _UpdateDataType();
    bool isValid = _CheckRequiredData(m_globalJsonVect);

    if (isValid) {
        for (auto it = m_globalJsonVect.begin(); it != m_globalJsonVect.end(); it++) {
            if (it->isRequired) {
                retVect.insert(retVect.end(), *it);
            } else if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

std::vector<sigmfJson_t> QSigMfCore::GetCaptureValues()
{
    std::vector<sigmfJson_t> retVect;
    _UpdateDataType();
    bool isValid = _CheckRequiredData(m_coreCapJsonVect);
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_coreCapJsonVect.begin(); it != m_coreCapJsonVect.end(); it++) {
            if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

std::vector<std::vector<sigmfJson_t> > QSigMfCore::GetCaptureArray()
{
    std::sort(m_coreCapJsonArr.begin(), m_coreCapJsonArr.end(), [](const std::vector<sigmfJson_t> &lhs, const std::vector<sigmfJson_t> &rhs) {
        return lhs.at(0).jsonVal < rhs.at(0).jsonVal;
    });

    std::vector< std::vector<sigmfJson_t> > retArr(m_coreCapJsonArr.size());
    int idx = 0;
    for (auto outIt = m_coreCapJsonArr.begin(); outIt != m_coreCapJsonArr.end(); outIt++) {
        for (auto inIt = outIt->begin(); inIt != outIt->end(); inIt++) {
            if (inIt->jsonVal.compare("")) {
                retArr.at(idx).insert(retArr.at(idx).end(), *inIt);
                qDebug() << "inserted " << inIt->jsonKey;
            }
        }
        idx++;
    }

    return retArr;
}

std::vector<sigmfJson_t> QSigMfCore::GetAnnotationValues()
{
    std::vector<sigmfJson_t> retVect;
    _UpdateDataType();
    bool isValid = _CheckRequiredData(m_coreAnnotJsonVect);
    qDebug() << "isValid: " << isValid;

    if (isValid) {
        for (auto it = m_coreAnnotJsonVect.begin(); it != m_coreAnnotJsonVect.end(); it++) {
            if (it->jsonVal.compare("")) {
                // Not an empty value
                retVect.insert(retVect.end(), *it);
                qDebug() << "inserted " << it->jsonKey;
            }
        }
    }

    return retVect;
}

std::vector<std::vector<sigmfJson_t> > QSigMfCore::GetAnnotationArray()
{
    std::sort(m_coreAnnotJsonArr.begin(), m_coreAnnotJsonArr.end(), [](const std::vector<sigmfJson_t> &lhs, const std::vector<sigmfJson_t> &rhs) {
        return lhs.at(0).jsonVal < rhs.at(0).jsonVal;
    });

    std::vector< std::vector<sigmfJson_t> > retArr(m_coreAnnotJsonArr.size());
    int idx = 0;
    for (auto outIt = m_coreAnnotJsonArr.begin(); outIt != m_coreAnnotJsonArr.end(); outIt++) {
        for (auto inIt = outIt->begin(); inIt != outIt->end(); inIt++) {
            if (inIt->jsonVal.compare("")) {
                retArr.at(idx).insert(retArr.at(idx).end(), *inIt);
                qDebug() << "inserted " << inIt->jsonKey;
            }
        }
        idx++;
    }

    return retArr;
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
    qDebug() << "hardware set";
    qDebug() << m_globalJsonVect.at(8).jsonKey << ": " << m_globalJsonVect.at(8).jsonVal;
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
    qDebug() << "in SetComplex";
    bool isCplx = str.compare("Complex") ? false : true;
    m_globalVars.SetComplex(isCplx);
    qDebug() << "complex? " << m_globalVars.GetComplexReal();
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

void QSigMfCore::SetSampleStart(int val)
{
    m_coreCapJsonVect.at(0).jsonVal = QString::number(val);
}

void QSigMfCore::SetDatetime(QDateTime dt)
{
    m_coreCapJsonVect.at(1).jsonVal = dt.toString(Qt::ISODateWithMs);
}

void QSigMfCore::SetFrequency(double val)
{
    m_coreCapJsonVect.at(2).jsonVal = QString::number(val);
}

void QSigMfCore::SetGlobalIndex(int val)
{
    m_coreCapJsonVect.at(3).jsonVal = QString::number(val);
}

void QSigMfCore::SetHeaderBytes(int val)
{
    m_coreCapJsonVect.at(4).jsonVal = QString::number(val);
}

void QSigMfCore::SetDatetimeEnabled(bool)
{
}

void QSigMfCore::SetAnnotSampleStart(int sr)
{
    m_coreAnnotJsonVect.at(0).jsonVal = QString::number(sr);
}

void QSigMfCore::SetSampleCount(int sc)
{
    m_coreAnnotJsonVect.at(1).jsonVal = QString::number(sc);
}

void QSigMfCore::SetFrequencyLower(double freq)
{
    m_coreAnnotJsonVect.at(2).jsonVal = QString::number(freq);
}

void QSigMfCore::SetFrequencyHigher(double freq)
{
    m_coreAnnotJsonVect.at(3).jsonVal = QString::number(freq);
}

void QSigMfCore::SetLabel(QString str)
{
    m_coreAnnotJsonVect.at(4).jsonVal = str;
}

void QSigMfCore::SetComment(QString str)
{
    m_coreAnnotJsonVect.at(5).jsonVal = str;
}

void QSigMfCore::SetGenerator(QString str)
{
    m_coreAnnotJsonVect.at(6).jsonVal = str;
}

void QSigMfCore::SetUuid(QString str)
{
    m_coreAnnotJsonVect.at(7).jsonVal = str;
}

void QSigMfCore::AddCapture()
{
    bool isValid = _CheckRequiredData(m_coreCapJsonVect);
    if (isValid) {
        m_coreCapJsonArr.insert(m_coreCapJsonArr.end(), m_coreCapJsonVect);
    }
}

void QSigMfCore::AddAnnotation()
{
    bool isValid = _CheckRequiredData(m_coreAnnotJsonVect);
    if (isValid) {
        m_coreAnnotJsonArr.insert(m_coreAnnotJsonArr.end(), m_coreAnnotJsonVect);
    }
}

bool QSigMfCore::_CheckRequiredData(std::vector<sigmfJson_t> vect)
{
    bool isCorrect = true;

    for (auto it = vect.begin(); it != vect.end(); it++) {
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
    qDebug() << "string: " << m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness();
    m_globalJsonVect.at(7).jsonVal = m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness();
    qDebug() << m_globalJsonVect.at(7).jsonKey << ": " << m_globalJsonVect.at(7).jsonVal;
    qDebug() << m_globalJsonVect.at(8).jsonKey << ": " << m_globalJsonVect.at(8).jsonVal;
}
