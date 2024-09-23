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
    void SetMetadataOnly(bool);
    void SetNumberChannels(int);
    void SetOffset(int);
    void SetRecorder(QString);
    void SetTrailingBytes(int);
    void SetVersion(QString);
    void SetGeoType(QString);
    void SetLat(double);
    void SetLon(double);
    void SetElevation(double);

signals:

protected:

private:

    class GlobalCore {
    public:
        void SetSampleRate(double sr){m_sampRate = sr;}
        void SetAuthor(QString a){m_author = a;}
        void SetMetaDoi(QString m){m_metaDoi = m;}
        void SetDataDoi(QString d){m_dataDoi = d;}
        void SetDescription(QString d){m_desc = d;}
        void SetLicense(QString l){m_license = l;}
        void SetMetadataOnly(bool m){m_metaOnly = m ? "true" : "false";}
        void SetNumberChannels(int n){m_numChans = n;}
        void SetOffset(int o){m_offset = o;}
        void SetRecorder(QString r){m_recorder = r;}
        void SetTrailingBytes(int b){m_trailBytes = b;}
        void SetVersion(QString v){m_version = v;}
        void SetGeoType(QString g){m_geoType = g;}
        void SetLat(double l){m_geo.SetLat(l);}
        void SetLon(double l){m_geo.SetLon(l);}
        void SetElevation(double e){m_geo.SetElv(e);}


    protected:

    private:
        double m_sampRate;
        QString m_author;
        QString m_metaDoi;
        QString m_dataDoi;
        QString m_desc;
        QString m_license;
        QString m_metaOnly;
        int m_numChans;
        int m_offset;
        QString m_recorder;
        int m_trailBytes;
        QString m_version;
        QString m_geoType;
        Geo m_geo;


    };

    GlobalCore globalVars;
    std::vector<varVals_t> m_jsonVect{
        {"core:sample_rate", "", true},
        {"core:author", "", false},
        {"core:description", "", false},
        {"core:license", "", false},
        {"core:metadata_only", "", false},
        {"core:number_channels", "", false},
        {"core:offset", "", false},
        {"core:datatype", "", true},
        {"core:hw", "", false}
    };
    bool _CheckRequiredData();



};

#endif // QSIGMFCORE_H
