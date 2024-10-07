#include "qsigmfglobal.h"

QSigMFGlobal::QSigMFGlobal()
{

}

QJsonObject QSigMFGlobal::GenerateGlobalJson()
{
    QJsonObject retObj;

    std::vector<sigmfJson_t> coreVect = m_sigmfCore.GetGlobalValues();
    for (auto it = coreVect.begin(); it != coreVect.end(); it++) {
        retObj.insert(it->jsonKey, it->jsonVal);
        qDebug() << "inserted " << it->jsonKey;
    }
    return retObj;
}

void QSigMFGlobal::SetSampleRate(double sr)
{
    m_sigmfCore.SetSampleRate(sr);
}

void QSigMFGlobal::SetAuthor(QString auth)
{
    m_sigmfCore.SetAuthor(auth);
}

void QSigMFGlobal::SetMetaDoi(QString doi)
{
    m_sigmfCore.SetMetaDoi(doi);
}

void QSigMFGlobal::SetDataDoi(QString doi)
{
    m_sigmfCore.SetDataDoi(doi);
}

void QSigMFGlobal::SetDescription(QString desc)
{
    m_sigmfCore.SetDescription(desc);
}

void QSigMFGlobal::SetLicense(QString l)
{
    m_sigmfCore.SetLicense(l);
}

void QSigMFGlobal::SetHardware(QString hw)
{
    m_sigmfCore.SetHardware(hw);
}

void QSigMFGlobal::SetMetadataOnly(bool isMetaOnly)
{
    m_sigmfCore.SetMetadataOnly(isMetaOnly);
}

void QSigMFGlobal::SetNumberChannels(int num)
{
    m_sigmfCore.SetNumberChannels(num);
}

void QSigMFGlobal::SetOffset(int offset)
{
    m_sigmfCore.SetOffset(offset);
}

void QSigMFGlobal::SetRecorder(QString rec)
{
    m_sigmfCore.SetRecorder(rec);
}

void QSigMFGlobal::SetTrailingBytes(int num)
{
    m_sigmfCore.SetTrailingBytes(num);
}

void QSigMFGlobal::SetVersion(QString v)
{
    m_sigmfCore.SetVersion(v);
}

void QSigMFGlobal::SetDataset(QString str)
{
    m_sigmfCore.SetDataset(str);
}

void QSigMFGlobal::SetSha512(QString str)
{
    m_sigmfCore.SetSha512(str);
}

void QSigMFGlobal::SetGeoType(QString gt)
{
    m_sigmfCore.SetGeoType(gt);
}

void QSigMFGlobal::SetLat(double lat)
{
    m_sigmfCore.SetLat(lat);
}

void QSigMFGlobal::SetLon(double lon)
{
    m_sigmfCore.SetLon(lon);
}

void QSigMFGlobal::SetElevation(double elv)
{
    m_sigmfCore.SetElevation(elv);
}

void QSigMFGlobal::SetComplex(const QString &str)
{
    m_sigmfCore.SetComplex(str);
}

void QSigMFGlobal::SetDataFormat(QString str)
{
    m_sigmfCore.SetDataFormat(str);
}

void QSigMFGlobal::SetEndianness(QString str)
{
    m_sigmfCore.SetEndianness(str);
}
