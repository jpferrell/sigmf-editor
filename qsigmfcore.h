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

    //QJsonObject GenerateGlobalJson();
    //QJsonObject GenerateCaptureJson();

    std::vector<sigmfJson_t> GetGlobalValues();
    std::vector<sigmfJson_t> GetCaptureValues();
    std::vector< std::vector<sigmfJson_t> > GetCaptureArray();
    std::vector<sigmfJson_t> GetAnnotationValues();
    std::vector< std::vector<sigmfJson_t> > GetAnnotationArray();

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

    // capture
    void SetSampleStart(int);
    void SetDatetime(QDateTime);
    void SetFrequency(double);
    void SetGlobalIndex(int);
    void SetHeaderBytes(int);
    void SetDatetimeEnabled(bool);

    // Annotations
    void SetAnnotSampleStart(int);
    void SetSampleCount(int);
    void SetFrequencyLower(double);
    void SetFrequencyHigher(double);
    void SetLabel(QString);
    void SetComment(QString);
    void SetGenerator(QString);
    void SetUuid(QString);

public slots:

    void AddCapture();
    void AddAnnotation();

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
    std::vector<sigmfJson_t> m_globalJsonVect {
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

    std::vector<sigmfJson_t> m_coreCapJsonVect {
        {"core:sample_start", "", true},
        {"core:datetime", "", false},
        {"core:frequency", "", false},
        {"core:global_index", "", false},
        {"core:header_bytes", "", false}
    };
    std::vector< std::vector<sigmfJson_t> > m_coreCapJsonArr;

    std::vector<sigmfJson_t> m_coreAnnotJsonVect {
        {"core:sample_start", "", true},
        {"core:sample_count", "", false},
        {"core:freq_lower_edge", "", false},
        {"core:freq_upper_edge", "", false},
        {"core:label", "", false},
        {"core:comment", "", false},
        {"core:generator", "", false},
        {"core:uuid", "", false}
    };
    std::vector< std::vector<sigmfJson_t> > m_coreAnnotJsonArr;

    bool _CheckRequiredData(std::vector<sigmfJson_t>);
    void _UpdateDataType();



};

#endif // QSIGMFCORE_H
