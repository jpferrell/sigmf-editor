#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_metafile("testfile.sigmf-meta")
    , m_datafile("testfile.sigmf-data")
    , m_dataFormat("")
    , m_realComplex("")
    , m_endianness("")
    , m_datatype("")
{
    ui->setupUi(this);

    _InitializeComboBoxes();

    connect(ui->configButton, &QPushButton::pressed, this, &MainWindow::_Configure);
    connect(ui->hardwareComboBox, &QComboBox::currentTextChanged, this, &MainWindow::_ChangeHardwareOption);

    m_metafile.open(QIODevice::WriteOnly);
}

MainWindow::~MainWindow()
{
    if (m_metafile.isOpen()) {
        m_metafile.close();
    }
    if (m_datafile.isOpen()) {
        m_datafile.close();
    }
    delete ui;
}

void MainWindow::_Configure()
{
    qDebug() << "Configure button pressed";
    _UpdateVariables();
    QByteArray jsonByteArray = _CreateJson();
    _WriteJsonFile(jsonByteArray);
}

void MainWindow::_ChangeHardwareOption(const QString &currentText)
{
    bool lineEnable = QString::compare(currentText, "Other") ? false : true;
    ui->otherHardwareLineEdit->setEnabled(lineEnable);
}

void MainWindow::_InitializeComboBoxes()
{
    ui->dataFormatComboBox->addItem("f32");
    ui->dataFormatComboBox->addItem("f64");
    ui->dataFormatComboBox->addItem("i32");
    ui->dataFormatComboBox->addItem("i16");
    ui->dataFormatComboBox->addItem("u32");
    ui->dataFormatComboBox->addItem("u16");
    ui->dataFormatComboBox->addItem("i8");
    ui->dataFormatComboBox->addItem("u8");

    ui->endianComboBox->addItem("Little Endian");
    ui->endianComboBox->addItem("Big Endian");

    ui->realComplexComboBox->addItem("Real");
    ui->realComplexComboBox->addItem("Complex");

    ui->hardwareComboBox->addItem("HackRF");
    ui->hardwareComboBox->addItem("RTL-SDR");
    ui->hardwareComboBox->addItem("LimeSDR");
    ui->hardwareComboBox->addItem("N210");
    ui->hardwareComboBox->addItem("E312");
    ui->hardwareComboBox->addItem("X300");
    ui->hardwareComboBox->addItem("X310");
    ui->hardwareComboBox->addItem("Other");
}

void MainWindow::_UpdateVariables()
{
    m_dataFormat = ui->dataFormatComboBox->currentText();
    m_realComplex = QString::compare(ui->realComplexComboBox->currentText(), "Real") ? "c" : "r";
    m_endianness = QString::compare(ui->endianComboBox->currentText(), "Little Endian") ? "_be" : "_le";
    m_datatype = m_realComplex + m_dataFormat + m_endianness;

    m_sampleRate = ui->sampleRateDoubleSpinBox->value();
    m_author = ui->authorLineEdit->text();
    m_collection = ui->collectionLineEdit->text();
    m_dataset = ui->datasetLineEdit->text();
    m_metaDoi = ui->metaDoiLineEdit->text();
    m_dataDoi = ui->dataDoiLineEdit->text();
    m_description = ui->descriptionPlainTextEdit->toPlainText();
    if (ui->otherHardwareLineEdit->isEnabled()) {
        m_hardware = ui->otherHardwareLineEdit->text();
    } else {
        m_hardware = ui->hardwareComboBox->currentText();
    }
    m_license = ui->licenseLineEdit->text();
    m_metadataOnly = ui->metaOnlyCheckBox->isChecked() ? "true" : "false";
    m_numChannels = ui->numChannelsSpinBox->value();
    m_offset = ui->offsetLineEdit->text().toInt();
    m_recorder = ui->recorderLineEdit->text();
    m_trailingBytes = ui->trailingBytesLineEdit->text().toInt();
    m_version = ui->versionLineEdit->text();
}

QByteArray MainWindow::_CreateJson()
{
    QJsonObject coreObj {
        {"core:author", m_author},
        {"core:collection", m_collection},
        {"core:data_doi", m_dataDoi},
        {"core:dataset", m_dataset},
        {"core:datatype", m_datatype},
        {"core:description", m_description},
        {"core:hardware", m_hardware},
        {"core:license", m_license},
        {"core:meta_doi", m_metaDoi},
        {"core:num_channels", m_numChannels},
        {"core:offset", m_offset},
        {"core:recorder", m_recorder},
        {"core:sample_rate", m_sampleRate},
        {"core:trailing_bytes", m_trailingBytes},
        {"core:version", m_version}
    };

    QJsonDocument jsonFile(coreObj);
    return jsonFile.toJson();
}

void MainWindow::_WriteJsonFile(QByteArray jsonByteArray)
{
    m_metafile.write(jsonByteArray);
}
