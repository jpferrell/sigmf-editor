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

#include <filesystem>

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
    void AddAnnotation();
    void AddCapture();
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
    QString m_dataFormat;
    QString m_realComplex;
    QString m_endianness;
    QString m_datatype;

    double m_sampleRate;
    QString m_author;
    QString m_collection;
    QString m_dataset;
    QString m_metaDoi;
    QString m_dataDoi;
    QString m_description;
    QString m_hardware;
    QString m_license;
    QString m_metadataOnly;
    int m_numChannels;
    int m_offset;
    QString m_recorder;
    int m_trailingBytes;
    QString m_version;

    // Captures Array
    QJsonArray m_captureJsonArray;
    std::vector<int> m_capturesStartIdxVect;

    // Annotations Array
    QJsonArray m_annotationJsonArray;
    std::vector<int> m_annotationStartIdxVect;

    void _InitializeComboBoxes();
    void _UpdateVariables();
    QByteArray _CreateJson();
    void _WriteJsonFile(QByteArray);
};
#endif // MAINWINDOW_H
