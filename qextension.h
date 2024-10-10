#ifndef QEXTENSION_H
#define QEXTENSION_H

#include <QObject>

#include "qsigmfbase.h"

class QExtension : public QSigMfBase
{
    Q_OBJECT
public:
    explicit QExtension(QObject *parent = nullptr);

    void SetEnable(bool en);
    bool GetEnabled();

signals:

public slots:

protected:

private:

    bool m_isEnabled;

};

#endif // QEXTENSION_H
