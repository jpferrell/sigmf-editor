#ifndef QSIGMFGLOBAL_H
#define QSIGMFGLOBAL_H

#include <QObject>
#include <QJsonObject>
#include <QString>

#include "include/qsigmfcore.h"
#include "include/qantenna.h"
#include "include/qsigmftypes.h"
#include "include/qtraceability.h"

class QSigMFGlobal : public QObject
{
    Q_OBJECT
public:
    QSigMFGlobal();

    QJsonObject GenerateGlobalJson();
    bool GetTraceabilityEnabled();
    bool GetAntennaEnabled();

signals:

public slots:

    void SetSampleRate(double);
    void SetAuthor(QString);
    void SetMetaDoi(QString);
    void SetDataDoi(QString);
    void SetDescription(QString);
    void SetLicense(QString);
    void SetHardware(QString);
    void SetMetadataOnly(bool);
    void SetNumberChannels(int);
    void SetOffset(int);
    void SetRecorder(QString);
    void SetTrailingBytes(int);
    void SetVersion(QString);
    void SetDataset(QString);
    void SetSha512(QString);
    void SetGeoType(QString);
    void SetLat(double);
    void SetLon(double);
    void SetElevation(double);
    void SetComplex(const QString&);
    void SetDataFormat(QString);
    void SetEndianness(QString);

    void SetAntennaEnabled(bool en);
    void SetAntennaModel(QString str);
    void SetAntennaType(QString str);
    void SetAntennaLowFreq(double f);
    void SetAntennaHighFreq(double f);
    void SetAntennaGain(double g);
    void SetAntennaHorizGain(double g);
    void SetAntennaVertGain(double g);
    void SetAntennaHorizBeamWidth(double w);
    void SetAntennaVertBeamWidth(double w);
    void SetAntennaXPolarDisc(double d);
    void SetAntennaVswr(double v);
    void SetAntennaCableLoss(double l);
    void SetAntennaSteerable(bool en);
    void SetAntennaMobile(bool en);
    void SetAntennaHagl(double h);

    void SetTraceabilityEnabled(bool en);
    void SetTraceLastModAuthor(QString author);
    void SetTraceLastModDatetime(QDateTime datetime);
    void SetTraceLastRevAuthor(QString author);
    void SetTraceLastRevDatetime(QDateTime datetime);
    void SetTraceRevision(int rev);
    void SetTraceAccount(QString account);
    void SetTraceContainer(QString container);
    void SetTraceFilepath(QString filepath);

    void AddExtension(QString name, QString version, QString optional);


protected:

private:

    QSigMfCore m_sigmfCore;
    QAntenna m_ant;
    QTraceability m_trace;

    QJsonArray m_extJsonArr;

};

#endif // QSIGMFGLOBAL_H
