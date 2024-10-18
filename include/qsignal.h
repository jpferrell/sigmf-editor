#ifndef QSIGNAL_H
#define QSIGNAL_H

#include <QObject>
#include "qextension.h"

class QSignal : public QExtension
{
    Q_OBJECT
public:
    explicit QSignal(QObject *parent = nullptr);
};

#endif // QSIGNAL_H
