#ifndef QEXTENSION_H
#define QEXTENSION_H

#include <QObject>
#include <QDebug>

#include "qsigmftypes.h"

class QExtension : public QObject
{
    Q_OBJECT
public:
    explicit QExtension(QObject *parent = nullptr);

    sigmfVector_t GetGlobalValues();
    sigmfVector_t GetCaptureValues();
    sigmfVector_t GetAnnotationValues();

    void SetEnable(bool en);
    bool GetEnabled();

signals:

public slots:

protected:

    void InitializeGlobalJsonVect(sigmfVector_t vect);
    void InitializeCaptureJsonVect(sigmfVector_t vect);
    void InitializeAnnotationJsonVect(sigmfVector_t vect);

    sigmfVector_t m_globalJsonVect;
    sigmfVector_t m_captureJsonVect;
    sigmfVector_t m_annotJsonVect;

    void InitializeGlobalJsonArray(sigmfArray_t arr);
    void InitializeCaptureJsonArray(sigmfArray_t arr);
    void InitializeAnnotationJsonArray(sigmfArray_t arr);

    sigmfArray_t m_globalJsonArray;
    sigmfArray_t m_captureJsonArray;
    sigmfArray_t m_annotJsonArray;

    bool _CheckRequiredData(sigmfVector_t vect);

private:

    bool m_isEnabled;

};

#endif // QEXTENSION_H
