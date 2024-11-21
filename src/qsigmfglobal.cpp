#include "include/qsigmfglobal.h"

/*!
 * \class QSigMFGlobal
 * \since v0.0.1
 *
 * \brief The QSigMFGlobal class provides methods for writing JSON objects of the
 * global values in the SigMF standard.
 */

/*!
 * \brief QSigMFGlobal::QSigMFGlobal constructs the QSigMFGlobal class and empty initializes
 * the extension classes.
 */
QSigMFGlobal::QSigMFGlobal():
    m_sigmfCore()
  , m_ant()
  , m_trace()
  , m_extJsonArr()
{
    connect(&this->m_ant, &QAntenna::extensionEnabled, this, &QSigMFGlobal::AddExtension);
}

/*!
 * \brief QSigMFGlobal::GenerateGlobalJson assembles the global JSON object from the extensions that
 * have global values.
 * \return (QJsonObject) that hold the JSON key/values for the global object.
 */
QJsonObject QSigMFGlobal::GenerateGlobalJson()
{
    QJsonObject retObj;

    sigmfMap_t coreMap = m_sigmfCore.GetGlobalMap();
    for (auto it = coreMap.cbegin(); it != coreMap.cend(); it++) {
        QString key = it->second.keys().at(0);
        retObj.insert(key, it->second.value(key));
    }

    /*
    std::vector<sigmfJson_t> coreVect = m_sigmfCore.GetGlobalValues();
    for (auto it = coreVect.begin(); it != coreVect.end(); it++) {
        retObj.insert(it->jsonKey, it->jsonVal);
        qDebug() << "inserted " << it->jsonKey;
    }
    if (m_sigmfCore.IsGeoValid()) {
        QJsonObject tmpObj = m_sigmfCore.GetGeoJson();
        retObj.insert("core:geolocation", tmpObj);
    }
    if (m_ant.GetEnabled()) {
        sigmfVector_t antVect = m_ant.GetGlobalValues();
        for (auto it = antVect.begin(); it != antVect.end(); it++) {
            retObj.insert(it->jsonKey, it->jsonVal);
            qDebug() << "inserted " << it->jsonKey;
        }
    }
    if (m_trace.GetEnabled()) {
        QJsonObject tmpObj;
        tmpObj = m_trace.GetGlobalLastMod();
        if (!tmpObj.isEmpty()) {
            retObj.insert("traceability:last_modified", tmpObj);
        }
        tmpObj = m_trace.GetGlobalLastRev();
        if (!tmpObj.isEmpty()) {
            retObj.insert("traceability:last_reviewed", tmpObj);
        }
        tmpObj = m_trace.GetGlobalOrigin();
        if (!tmpObj.isEmpty()) {
            retObj.insert("traceability:origin", tmpObj);
        }
        QString rev = m_trace.GetGlobalRevision();
        if (QString::compare(rev, "")) {
            retObj.insert("traceability:revision", rev);
        }
    }
    retObj.insert("core:extensions", m_extJsonArr);
    */

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

bool QSigMFGlobal::GetAntennaEnabled()
{
    return m_ant.GetEnabled();
}

void QSigMFGlobal::SetAntennaEnabled(bool en)
{
    m_ant.SetEnable(en);
}

void QSigMFGlobal::SetAntennaModel(QString str)
{
    m_ant.SetModel(str);
}

void QSigMFGlobal::SetAntennaType(QString str)
{
    m_ant.SetType(str);
}

void QSigMFGlobal::SetAntennaLowFreq(double f)
{
    m_ant.SetLowFreq(f);
}

void QSigMFGlobal::SetAntennaHighFreq(double f)
{
    m_ant.SetHighFreq(f);
}

void QSigMFGlobal::SetAntennaGain(double g)
{
    m_ant.SetGain(g);
}

void QSigMFGlobal::SetAntennaHorizGain(double g)
{
    m_ant.SetHorizGain(g);
}

void QSigMFGlobal::SetAntennaVertGain(double g)
{
    m_ant.SetVertGain(g);
}

void QSigMFGlobal::SetAntennaHorizBeamWidth(double w)
{
    m_ant.SetHorizBeamWidth(w);
}

void QSigMFGlobal::SetAntennaVertBeamWidth(double w)
{
    m_ant.SetVertBeamWidth(w);
}

void QSigMFGlobal::SetAntennaXPolarDisc(double d)
{
    m_ant.SetXPolarDisc(d);
}

void QSigMFGlobal::SetAntennaVswr(double v)
{
    m_ant.SetVswr(v);
}

void QSigMFGlobal::SetAntennaCableLoss(double l)
{
    m_ant.SetCableLoss(l);
}

void QSigMFGlobal::SetAntennaSteerable(bool en)
{
    m_ant.SetSteerable(en);
}

void QSigMFGlobal::SetAntennaMobile(bool en)
{
    m_ant.SetMobile(en);
}

void QSigMFGlobal::SetAntennaHagl(double h)
{
    m_ant.SetHagl(h);
}

void QSigMFGlobal::SetTraceabilityEnabled(bool en)
{
    m_trace.SetEnable(en);
}

void QSigMFGlobal::SetTraceLastModAuthor(QString author)
{
    m_trace.SetGlobalLastModAuthor(author);
}

void QSigMFGlobal::SetTraceLastModDatetime(QDateTime datetime)
{
    m_trace.SetGlobalLastModDatetime(datetime.toString(Qt::ISODateWithMs));
}

void QSigMFGlobal::SetTraceLastRevAuthor(QString author)
{
    m_trace.SetGlobalLastRevAuthor(author);
}

void QSigMFGlobal::SetTraceLastRevDatetime(QDateTime datetime)
{
    m_trace.SetGlobalLastRevDatetime(datetime.toString(Qt::ISODateWithMs));
}

void QSigMFGlobal::SetTraceRevision(int rev)
{
    m_trace.SetRevision(rev);
}

void QSigMFGlobal::SetTraceAccount(QString account)
{
    m_trace.SetOriginAccount(account);
}

void QSigMFGlobal::SetTraceContainer(QString container)
{
    m_trace.SetOriginContainer(container);
}

void QSigMFGlobal::SetTraceFilepath(QString filepath)
{
    m_trace.SetOriginFilepath(filepath);
}

void QSigMFGlobal::AddExtension(QString name, QString version, QString optional)
{
    qDebug() << "Add extension called for " << name;
    QJsonObject tmp;
    tmp.insert("name", name);
    tmp.insert("version", version);
    tmp.insert("optional", optional);
    m_extJsonArr.append(tmp);
}
