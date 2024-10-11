#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QCheckBox>
#include <QCryptographicHash>

#include <filesystem>

#include "include/qsigmfglobal.h"
#include "include/qsigmfcapture.h"
#include "include/qsigmfannotation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const QString DATAFILEEXT = ".sigmf-data";
    const QString METAFILEEXT = ".sigmf-meta";

public slots:

    void Configure();
    void ChangeHardwareOption(const QString &);
    void ChangeDatetimeEnable();
    void OpenDataFile();
    void ExitApplication();
    void MatchCheckBox(int, QCheckBox &);

signals:


private:
    Ui::MainWindow *ui;

    QFile m_metafile;
    QFile m_datafile;

    QString m_dataFilepath;
    QString m_metaFilepath;
    QString m_dataFilestem;
    QString m_metaFilestem;

    // Global Object
    //QSigMfCore m_sigmfCore;
    QSigMFGlobal m_sigmfGlobal;

    // Captures Array
    QSigMFCapture m_sigmfCapture;
    QJsonArray m_captureJsonArray;
    std::vector<int> m_capturesStartIdxVect;

    // Annotations Array
    QSigMFAnnotation m_sigmfAnnotation;
    QJsonArray m_annotationJsonArray;
    std::vector<int> m_annotationStartIdxVect;

    // Initializations
    void _InitializeComboBoxes();
    void _InitializeGeneralConnections();
    void _InitializeCoreConnections();
    void _InitializeSignalExtConnections();
    void _InitializeAdbsExtConnections();
    void _InitializeWifiExtConnections();
    void _InitializeAntennaExtConnections();

    void _UpdateVariables();
    QByteArray _CreateJson();
    void _WriteJsonFile(QByteArray);
    bool _CheckValidValue(QObject *);

};
#endif // MAINWINDOW_H
