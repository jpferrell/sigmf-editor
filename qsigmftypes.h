#ifndef QSIGMFTYPES_H
#define QSIGMFTYPES_H

#include <QString>

class Geo {
public:
    void SetLat(double lat){m_lat = lat;}
    void SetLon(double lon){m_lon = lon;}
    void SetElv(double elv){m_elv = elv;}
    double GetLat(){return m_lat;}
    double GetLon(){return m_lon;}
    double GetElv(){return m_elv;}
protected:

private:

    double m_lat;
    double m_lon;
    double m_elv;
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

#endif // QSIGMFTYPES_H
