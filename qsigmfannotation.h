#ifndef QSIGMFANNOTATION_H
#define QSIGMFANNOTATION_H

#include <QObject>
#include <QJsonArray>

#include "qsigmfcore.h"
#include "qsigmftypes.h"

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
    void AddAnnotation();

protected:

private:

    QSigMfCore m_sigmfCore;
    std::vector< std::vector<sigmfJson_t> > m_annotVect;

};

#endif // QSIGMFANNOTATION_H
