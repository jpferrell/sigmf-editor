QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/qtraceability.cpp \
    src/qsignal.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/qadsb.cpp \
    src/qantenna.cpp \
    src/qcapturedetails.cpp \
    src/qextension.cpp \
    src/qsigmfannotation.cpp \
    src/qsigmfbase.cpp \
    src/qsigmfcapture.cpp \
    src/qsigmfcore.cpp \
    src/qsigmfglobal.cpp \
    src/qwifi.cpp

HEADERS += \
    include/qtraceability.h \
    include/mainwindow.h \
    include/qadsb.h \
    include/qantenna.h \
    include/qcapturedetails.h \
    include/qextension.h \
    include/qsigmfannotation.h \
    include/qsigmfbase.h \
    include/qsigmfcapture.h \
    include/qsigmfcore.h \
    include/qsigmfglobal.h \
    include/qsigmftypes.h \
    include/qwifi.h \
    include/qsignal.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/warning_icon.qrc
