#include "include/qsignal.h"

QSignal::QSignal(QObject *parent)
    : QExtension{{}, {}, {}, parent}
{

}
