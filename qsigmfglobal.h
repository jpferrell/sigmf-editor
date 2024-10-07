#ifndef QSIGMFGLOBAL_H
#define QSIGMFGLOBAL_H

#include <QObject>
#include <QJsonObject>
#include <QString>

#include "qsigmfcore.h"
#include "qsigmftypes.h"

class QSigMFGlobal : public QObject
{
    Q_OBJECT
public:
    QSigMFGlobal();

    QJsonObject GenerateGlobalJson();

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

protected:

private:

    QSigMfCore m_sigmfCore;

};

#endif // QSIGMFGLOBAL_H
