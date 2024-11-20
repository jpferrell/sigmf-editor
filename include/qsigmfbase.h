#ifndef QSIGMFBASE_H
#define QSIGMFBASE_H

#include <QObject>
#include <QDebug>

#include "include/qsigmftypes.h"

class QSigMfBase : public QObject
{
    Q_OBJECT
public:
    explicit QSigMfBase(qstringVect_t reqGlobeVect, qstringVect_t reqCapVect, qstringVect_t reqAnnotVect, QObject *parent = nullptr);

    sigmfMap_t GetGlobalMap();
    sigmfMap_t GetCaptureMap();
    sigmfMap_t GetAnnotationMap();

signals:

public slots:

protected:

    sigmfMap_t m_globalJsonMap;
    sigmfMap_t m_captureJsonMap;
    sigmfMap_t m_annotJsonMap;

    qstringVect_t m_requiredGlobalKeys;
    qstringVect_t m_requiredCaptureKeys;
    qstringVect_t m_requiredAnnotKeys;

private:

    bool _CheckRequiredData(sigmfMap_t map, qstringVect_t requiredKeys);
};

#endif // QSIGMFBASE_H
