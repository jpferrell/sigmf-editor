#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_metafile()
    , m_datafile()
    , m_dataFilepath(".")
    , m_metaFilepath(".")
    , m_dataFilestem("out")
    , m_metaFilestem("out")
    , m_captureJsonArray()
    , m_capturesStartIdxVect()
    , m_sigmfAnnotation()
    , m_annotationJsonArray()
    , m_annotationStartIdxVect()

{
    ui->setupUi(this);

    _InitializeComboBoxes();

    connect(ui->writeButton, &QPushButton::pressed, this, &MainWindow::Configure);
    connect(ui->hardwareComboBox, &QComboBox::currentTextChanged, this, &MainWindow::ChangeHardwareOption);
    connect(ui->addAnnotationPushButton, &QPushButton::pressed, this, &MainWindow::AddAnnotation);
    //connect(ui->addCapturePushButton, &QPushButton::pressed, this, &MainWindow::AddCapture);
    connect(ui->datetimeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::ChangeDatetimeEnable);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::OpenDataFile);
    connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::ExitApplication);
    // Have both of the connected checkboxes change state when one of them changes state from user
    connect(ui->globalTracebilityEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->globalTracebilityEnabledCheckbox->checkState(), *ui->annotationTraceabilityEnabledCheckbox);});
    connect(ui->annotationTraceabilityEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->annotationTraceabilityEnabledCheckbox->checkState(), *ui->globalTracebilityEnabledCheckbox);});
    connect(ui->captureDetailsEnabledCheckBox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->captureDetailsEnabledCheckBox->checkState(), *ui->annotationCapDetsEnabledCheckbox);});
    connect(ui->annotationCapDetsEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->annotationCapDetsEnabledCheckbox->checkState(), *ui->captureDetailsEnabledCheckBox);});

    // SigMF Core Global connections
    connect(ui->realComplexComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetComplex);
    connect(ui->dataFormatComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetDataFormat);
    connect(ui->endianComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetEndianness);
    connect(ui->authorLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAuthor);
    connect(ui->sampleRateDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetSampleRate);
    connect(ui->metaDoiLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetMetaDoi);
    connect(ui->dataDoiLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetDataDoi);
    //connect(ui->descriptionPlainTextEdit, &QPlainTextEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetDescription);
    connect(ui->licenseLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetLicense);
    connect(ui->hardwareComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetHardware);
    connect(ui->otherHardwareLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetHardware);
    connect(ui->metaOnlyCheckBox, &QCheckBox::stateChanged, &m_sigmfGlobal, &QSigMFGlobal::SetMetadataOnly);
    connect(ui->numChannelsSpinBox, &QSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetNumberChannels);
    connect(ui->offsetSpinBox, &QSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetOffset);
    connect(ui->recorderLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetRecorder);
    connect(ui->trailingBytesSpinBox, &QSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetTrailingBytes);
    connect(ui->versionLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetVersion);

    // SigMF Core Capture Connections
    connect(ui->sampStartSpinBox, &QSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetSampleStart);
    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, &m_sigmfCapture, &QSigMFCapture::SetDatetime);
    connect(ui->datetimeCheckBox, &QCheckBox::stateChanged, &m_sigmfCapture, &QSigMFCapture::SetDatetimeEnabled);
    connect(ui->frequencyDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetFrequency);
    connect(ui->globalIdxSpinBox, &QSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetGlobalIndex);
    connect(ui->headerBytesSpinBox, &QSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetHeaderBytes);
    connect(ui->addCapturePushButton, &QPushButton::clicked, &m_sigmfCapture, &QSigMFCapture::AddCapture);

    // SigMF Core Annotation Connections
    connect(ui->sampStartAnnotSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetSampleStart);
    connect(ui->sampCntAnnotSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetSampleCount);
    connect(ui->freqLowerEdgeDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetFrequencyLower);
    connect(ui->freqUpperEdgeDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetFrequencyHigher);
    connect(ui->labelAnnotLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetLabel);
    //connect(ui->commentAnnotPlainTextEdit, &QPlainTextEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetComment);
    connect(ui->generatorLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetGenerator);
    connect(ui->uuidLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetUuid);
    connect(ui->addAnnotationPushButton, &QPushButton::clicked, &m_sigmfAnnotation, &QSigMFAnnotation::AddAnnotation);

    if(qobject_cast<QCheckBox*>(ui->globalSpatialEnabledCheckBox)) {
        qDebug() << "Is checkbox";
    }
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

void MainWindow::Configure()
{
    qDebug() << "Configure button pressed";
    _UpdateVariables();
    QByteArray jsonByteArray = _CreateJson();
    _WriteJsonFile(jsonByteArray);
}

void MainWindow::ChangeHardwareOption(const QString &currentText)
{
    bool lineEnable = QString::compare(currentText, "Other") ? false : true;
    ui->otherHardwareLineEdit->setEnabled(lineEnable);
}

void MainWindow::AddAnnotation()
{
    qDebug() << "Add annotation button pressed";
    int sampStart = ui->sampStartAnnotSpinBox->text().toInt();
    int sampCnt = ui->sampCntAnnotSpinBox->text().toInt();
    double freqLowerEdge = ui->freqLowerEdgeDoubleSpinBox->value();
    double freqUpperEdge = ui->freqUpperEdgeDoubleSpinBox->value();
    QString label = ui->labelAnnotLineEdit->text();
    QString comment = ui->commentAnnotPlainTextEdit->toPlainText();
    QString generator = ui->generatorLineEdit->text();
    QString uuid = ui->uuidLineEdit->text();
    QJsonObject jsonObj = {
        {"core:sample_start", sampStart},
        {"core:sample_count", sampCnt},
        {"core:freq_lower_edge", freqLowerEdge},
        {"core:freq_upper_edge", freqUpperEdge},
        {"core:label", label},
        {"core:comment", comment},
        {"core:generator", generator},
        {"core:uuid", uuid}
    };
    if(ui->adsbEnabledCheckBox->isChecked()) {
        QJsonValue downlink =  QString::compare(ui->downlinkFormatComboBox->currentText(), "Mode S Short (11)") ? 17 : 11;
        jsonObj.insert("adsb:downlink_format", downlink);
        jsonObj.insert("adsb:message_type", ui->adsbMsgTypeComboBox->value());
        jsonObj.insert("adsb:ICA_address", ui->icaAddrDoubleSpinBox->value());
        jsonObj.insert("adsb:binary", ui->adsbBinaryPlainTextEdit->toPlainText());
    }

    m_annotationJsonArray.append(jsonObj);
}

void MainWindow::AddCapture()
{
    /*
    qDebug() << "Add capture button pressed";
    int sampStart = ui->sampStartSpinBox->text().toInt(); // Not working atm
    double freq = ui->frequencyDoubleSpinBox->value();
    int globalIdx = ui->globalIdxSpinBox->text().toInt();
    int headerBytes = ui->headerBytesSpinBox->text().toInt();
    QString datetime = "";
    if (ui->dateTimeEdit->isEnabled()) {
        datetime = ui->dateTimeEdit->dateTime().toString(Qt::ISODateWithMs);
    }
    qDebug() << "datetime: " << datetime;

    QJsonObject jsonObj = {
        {"core:sample_start", sampStart},
        {"core:datetime", datetime},
        {"core:frequency", freq},
        {"core:global_index", globalIdx},
        {"core:header_bytes", headerBytes}
    };

    //m_capturesVect.push_back(jsonObj);
    m_captureJsonArray.append(jsonObj);
    */
}

void MainWindow::ChangeDatetimeEnable()
{
    ui->dateTimeEdit->setEnabled(ui->datetimeCheckBox->isChecked());
}

void MainWindow::OpenDataFile()
{
    qDebug() << "In OpenDataFile";
    QString filename = QFileDialog::getOpenFileName(this, tr("Open SigMF data file"), ".", tr("SigMF Files (*.sigmf-data);;All files (*.*)"));
    qDebug() << "filename: " << filename;
    std::filesystem::path filePath(filename.toStdString());
    m_dataFilepath = QString::fromStdString(filePath.parent_path().string());
    m_dataFilestem = QString::fromStdString(filePath.stem().string());
    qDebug() << "datafilepath: " << m_dataFilepath;
    qDebug() << "datafilestem: " << m_dataFilestem;

    ui->inFilepathLineEdit->setText(m_dataFilepath);
    ui->outFilepathLineEdit->setText(m_dataFilepath);
    ui->inFilestubLineEdit->setText(m_dataFilestem);
    ui->outFilestubLineEdit->setText(m_dataFilestem);
}

void MainWindow::ExitApplication()
{
    QApplication::quit();
}

void MainWindow::MatchCheckBox(int state, QCheckBox &sender)
{
    sender.setCheckState(static_cast<Qt::CheckState>(state));
}

void MainWindow::_InitializeComboBoxes()
{
    ui->dataFormatComboBox->addItem("");
    ui->dataFormatComboBox->addItem("f32");
    ui->dataFormatComboBox->addItem("f64");
    ui->dataFormatComboBox->addItem("i32");
    ui->dataFormatComboBox->addItem("i16");
    ui->dataFormatComboBox->addItem("u32");
    ui->dataFormatComboBox->addItem("u16");
    ui->dataFormatComboBox->addItem("i8");
    ui->dataFormatComboBox->addItem("u8");

    ui->endianComboBox->addItem("");
    ui->endianComboBox->addItem("Little Endian");
    ui->endianComboBox->addItem("Big Endian");

    ui->realComplexComboBox->addItem("");
    ui->realComplexComboBox->addItem("Real");
    ui->realComplexComboBox->addItem("Complex");

    ui->hardwareComboBox->addItem("");
    ui->hardwareComboBox->addItem("HackRF");
    ui->hardwareComboBox->addItem("RTL-SDR");
    ui->hardwareComboBox->addItem("LimeSDR");
    ui->hardwareComboBox->addItem("N210");
    ui->hardwareComboBox->addItem("E312");
    ui->hardwareComboBox->addItem("X300");
    ui->hardwareComboBox->addItem("X310");
    ui->hardwareComboBox->addItem("Other");

    ui->downlinkFormatComboBox->addItem("");
    ui->downlinkFormatComboBox->addItem("Mode S Short (11)");
    ui->downlinkFormatComboBox->addItem("Mode S Extended (17)");

    ui->sigDetailMultiplexComboBox->addItem("");
    ui->sigDetailMultiplexComboBox->addItem("TDM");
    ui->sigDetailMultiplexComboBox->addItem("FDM");
    ui->sigDetailMultiplexComboBox->addItem("CDM");
    ui->sigDetailMultiplexComboBox->addItem("OFDM");
    ui->sigDetailMultiplexComboBox->addItem("SDM");
    ui->sigDetailMultiplexComboBox->addItem("PDM");

    ui->sigDetailDuplexComboBox->addItem("");
    ui->sigDetailDuplexComboBox->addItem("TDD");
    ui->sigDetailDuplexComboBox->addItem("FDD");

    ui->sigDetailSymVarComboBox->addItem("");
    ui->sigDetailSymVarComboBox->addItem("Differential");
    ui->sigDetailSymVarComboBox->addItem("Offset");

    ui->sigDetailCarVarComboBox->addItem("");
    ui->sigDetailCarVarComboBox->addItem("With Carrier");
    ui->sigDetailCarVarComboBox->addItem("Suppressed Carrier");
    ui->sigDetailCarVarComboBox->addItem("Reduced Carrier");
    ui->sigDetailCarVarComboBox->addItem("Single Carrier");
    ui->sigDetailCarVarComboBox->addItem("Multi Carrier");

    ui->sigDetailModTypeComboBox->addItem("");
    ui->sigDetailModTypeComboBox->addItem("AM");
    ui->sigDetailModTypeComboBox->addItem("FM");
    ui->sigDetailModTypeComboBox->addItem("PM");
    ui->sigDetailModTypeComboBox->addItem("SSB");
    ui->sigDetailModTypeComboBox->addItem("DSB");
    ui->sigDetailModTypeComboBox->addItem("VSB");
    ui->sigDetailModTypeComboBox->addItem("ASK");
    ui->sigDetailModTypeComboBox->addItem("FSK");
    ui->sigDetailModTypeComboBox->addItem("PSK");
    ui->sigDetailModTypeComboBox->addItem("QAM");
    ui->sigDetailModTypeComboBox->addItem("OOK");
    ui->sigDetailModTypeComboBox->addItem("CPM");
    ui->sigDetailModTypeComboBox->addItem("MSK");

    ui->sigDetailSpreadComboBox->addItem("");
    ui->sigDetailSpreadComboBox->addItem("FHSS");
    ui->sigDetailSpreadComboBox->addItem("THSS");
    ui->sigDetailSpreadComboBox->addItem("DSSS");
    ui->sigDetailSpreadComboBox->addItem("CSS");

    ui->sigDetailTypeComboBox->addItem("");
    ui->sigDetailTypeComboBox->addItem("Analog");
    ui->sigDetailTypeComboBox->addItem("Digital");

    ui->sigDetaillMultAccComboBox->addItem("");
    ui->sigDetaillMultAccComboBox->addItem("FDMA");
    ui->sigDetaillMultAccComboBox->addItem("OFDMA");
    ui->sigDetaillMultAccComboBox->addItem("TDMA");
    ui->sigDetaillMultAccComboBox->addItem("CDMA");
    ui->sigDetaillMultAccComboBox->addItem("SDMA");
    ui->sigDetaillMultAccComboBox->addItem("PDMA");
}

void MainWindow::_UpdateVariables()
{
    m_metaFilepath = ui->outFilepathLineEdit->text();
    m_metaFilestem = ui->outFilestubLineEdit->text();
}

QByteArray MainWindow::_CreateJson()
{
    //QJsonObject globalObj = m_sigmfCore.GenerateGlobalJson();
    QJsonObject globalObj = m_sigmfGlobal.GenerateGlobalJson();
    //QJsonObject captureObj = m_sigmfCapture.GenerateCaptureJson();
    QJsonArray captureJsonArr = m_sigmfCapture.GenerateCaptureJsonArray();
    QJsonArray annotationJsonArr = m_sigmfAnnotation.GenerateAnnotationJsonArray();

    QJsonObject overallObj;
    /*
    if(m_annotationJsonArray.size()) {
        overallObj.insert("annotations", m_annotationJsonArray);
    }
    if(m_captureJsonArray.size()) {
        overallObj.insert("captures", m_captureJsonArray);
    }
    */
    overallObj.insert("global", globalObj);
    //overallObj.insert("captures", captureObj);
    overallObj.insert("captures", captureJsonArr);
    overallObj.insert("annotations", annotationJsonArr);
    QJsonDocument jsonFileCore(overallObj);
    return jsonFileCore.toJson();
}

void MainWindow::_WriteJsonFile(QByteArray jsonByteArray)
{
    //m_metafile.open(QIODevice::WriteOnly);
    m_metafile.setFileName(m_metaFilepath+tr("/")+m_metaFilestem+METAFILEEXT);
    m_metafile.open(QIODevice::WriteOnly);
    m_metafile.write(jsonByteArray);
    m_metafile.flush();
    m_metafile.close();
}

bool MainWindow::_CheckValidValue(QObject *obj)
{
    if(qobject_cast<QCheckBox*>(obj)) {
        qDebug() << "Is checkbox";
    } else if (qobject_cast<QSpinBox*>(obj)) {
        qDebug() << "Is SpinBox";
    } else if (qobject_cast<QDoubleSpinBox*>(obj)) {
        qDebug() << "Is DoubleSpinBox";
    } else if (qobject_cast<QComboBox*>(obj)) {
        qDebug() << "Is ComboBox";
    } else if (qobject_cast<QLineEdit*>(obj)) {
        qDebug() << "Is LineEdit";
    } else if (qobject_cast<QTextEdit*>(obj)) {
        qDebug() << "Is TextEdit";
    } else if (qobject_cast<QPlainTextEdit*>(obj)) {
        qDebug() << "Is PlainTextEdit";
    }
    return true;
}
