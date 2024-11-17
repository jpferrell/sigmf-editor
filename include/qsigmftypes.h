#ifndef QSIGMFTYPES_H
#define QSIGMFTYPES_H

#include <QString>
#include <vector>

class Geo {
public:
    void SetLat(double lat){m_lat = QString::number(lat);}
    void SetLon(double lon){m_lon = QString::number(lon);}
    void SetElv(double elv){m_elv = QString::number(elv);}
    QString GetLat(){return m_lat;}
    QString GetLon(){return m_lon;}
    QString GetElv(){return m_elv;}
protected:

private:

    QString m_lat;
    QString m_lon;
    QString m_elv;
};

typedef struct bearing {
    double azimuth;
    double elevation;
    double range;
    double rangeRate;
    double azimuthErr;
    double elevationErr;
    double rangeErr;
    double rangeRateErr;
} bearing_t;

typedef struct sigmfJson {
    QString jsonKey;
    QString jsonVal;
    bool isRequired;
} sigmfJson_t;

typedef struct dataChange {
    QString author;
    QString datetime;
} dataChange_t;

typedef struct origin {
    QString account;
    QString container;
    QString file_path;
} origin_t;

typedef std::vector<sigmfJson_t> sigmfVector_t;
typedef std::vector< std::vector<sigmfJson_t> > sigmfArray_t;

#endif // QSIGMFTYPES_H
