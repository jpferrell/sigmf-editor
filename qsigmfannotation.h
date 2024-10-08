#ifndef QSIGMFANNOTATION_H
#define QSIGMFANNOTATION_H

#include <QObject>
#include <QJsonArray>

#include "qsigmfcore.h"
#include "qsigmftypes.h"
#include "qcapturedetails.h"

class QSigMFAnnotation : public QObject
{
    Q_OBJECT
public:
    QSigMFAnnotation();

    QJsonArray GenerateAnnotationJsonArray();

public slots:

    void SetSampleStart(int);
    void SetSampleCount(int);
    void SetFrequencyLower(double);
    void SetFrequencyHigher(double);
    void SetLabel(QString);
    void SetComment(QString);
    void SetGenerator(QString);
    void SetUuid(QString);

    void SetCapDetEnabled(bool);
    void SetCapDetSnr(double);
    void SetCapDetSigRefNum(QString);

    void AddAnnotation();


protected:

private:

    QSigMfCore m_sigmfCore;
    QCaptureDetails m_capDets;
    std::vector< std::vector<sigmfJson_t> > m_annotVect;

};

#endif // QSIGMFANNOTATION_H
