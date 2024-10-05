#ifndef QSIGMFCORE_H
#define QSIGMFCORE_H

#include <QObject>
#include <QJsonObject>
#include "qsigmftypes.h"


class QSigMfCore : public QObject
{
    Q_OBJECT
public:
    explicit QSigMfCore(QObject *parent = nullptr);

    QJsonObject GenerateJson();

    typedef struct varVals {
        QString jsonKey;
        QString jsonVal;
        bool isRequired;
    } varVals_t;

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

signals:

protected:

private:

    class GlobalCore {
    public:

        GlobalCore(){m_complexReal=""; m_dataFormat=""; m_endianness="";}

        void SetGeoType(QString g){m_geoType = g;}
        void SetLat(double l){m_geo.SetLat(l);}
        void SetLon(double l){m_geo.SetLon(l);}
        void SetElevation(double e){m_geo.SetElv(e);}
        void SetComplex(bool isCplx){m_complexReal = isCplx ? "c": "r";}
        void SetDataFormat(QString df){m_dataFormat = df;}
        void SetEndianness(QString e){m_endianness = e;}

        QString GetComplexReal(){return m_complexReal;}
        QString GetDataFormat(){return m_dataFormat;}
        QString GetEndianness(){return m_endianness;}

    protected:

    private:
        QString m_geoType;
        Geo m_geo;

        QString m_complexReal;
        QString m_dataFormat;
        QString m_endianness;


    };

    GlobalCore m_globalVars;
    std::vector<varVals_t> m_jsonVect{
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
    };
    bool _CheckRequiredData();
    void _UpdateDataType();



};

#endif // QSIGMFCORE_H
