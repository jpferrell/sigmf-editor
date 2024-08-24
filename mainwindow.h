#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void _Configure();
    void _ChangeHardwareOption(const QString &);

signals:


private:
    Ui::MainWindow *ui;

    QFile m_metafile;
    QFile m_datafile;

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
    int m_sampleStartCap;
    QString m_datetime;
    double m_centerFrequency;
    int m_globalIndex;
    int m_headerBytes;

    // Annotations Array
    int m_sampleStartAnnot;
    int m_sampleCount;
    int m_freqLowerEdge;
    int m_freqUpperEdge;
    QString m_labelAnnot;
    QString m_commentAnnot;
    QString m_generatorAnnot;
    QString m_uuidAnnot;

    void _InitializeComboBoxes();
    void _UpdateVariables();
    QByteArray _CreateJson();
    void _WriteJsonFile(QByteArray);
};
#endif // MAINWINDOW_H
