#include "include/mainwindow.h"
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

    _InitializeGeneralConnections();
    _InitializeCoreConnections();
    _InitializeSignalExtConnections();
    _InitializeAdbsExtConnections();
    _InitializeWifiExtConnections();
    _InitializeAntennaExtConnections();
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

    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha512);
    hash.addData(&m_datafile);
    m_sigmfGlobal.SetSha512(hash.result().toHex().toUpper());
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

void MainWindow::_InitializeGeneralConnections()
{
    connect(ui->writeButton, &QPushButton::pressed, this, &MainWindow::Configure);
    connect(ui->hardwareComboBox, &QComboBox::currentTextChanged, this, &MainWindow::ChangeHardwareOption);
    connect(ui->datetimeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::ChangeDatetimeEnable);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::OpenDataFile);
    connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::ExitApplication);
    // Have both of the connected checkboxes change state when one of them changes state from user
    connect(ui->globalTracebilityEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->globalTracebilityEnabledCheckbox->checkState(), *ui->annotationTraceabilityEnabledCheckbox);});
    connect(ui->annotationTraceabilityEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->annotationTraceabilityEnabledCheckbox->checkState(), *ui->globalTracebilityEnabledCheckbox);});
    connect(ui->captureDetailsEnabledCheckBox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->captureDetailsEnabledCheckBox->checkState(), *ui->annotationCapDetsEnabledCheckbox);});
    connect(ui->annotationCapDetsEnabledCheckbox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->annotationCapDetsEnabledCheckbox->checkState(), *ui->captureDetailsEnabledCheckBox);});
    connect(ui->antennaEnableCheckBox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->antennaEnableCheckBox->checkState(), *ui->annotationAntennaEnabledCheckBox);});
    connect(ui->annotationAntennaEnabledCheckBox, &QCheckBox::stateChanged, this, [=] () {this->MatchCheckBox(ui->annotationAntennaEnabledCheckBox->checkState(), *ui->antennaEnableCheckBox);});
}

void MainWindow::_InitializeCoreConnections()
{
    // SigMF Core Global connections
    connect(ui->realComplexComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetComplex);
    connect(ui->dataFormatComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetDataFormat);
    connect(ui->endianComboBox, &QComboBox::currentTextChanged, &m_sigmfGlobal, &QSigMFGlobal::SetEndianness);
    connect(ui->authorLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAuthor);
    connect(ui->sampleRateDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetSampleRate);
    connect(ui->metaDoiLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetMetaDoi);
    connect(ui->dataDoiLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetDataDoi);
    connect(ui->descriptionPlainTextEdit, &QPlainTextEdit::textChanged, this, [=] () {m_sigmfGlobal.SetDescription(ui->descriptionPlainTextEdit->toPlainText());});
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
    connect(ui->commentAnnotPlainTextEdit, &QPlainTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetComment(ui->commentAnnotPlainTextEdit->toPlainText());});
    connect(ui->generatorLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetGenerator);
    connect(ui->uuidLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetUuid);
    connect(ui->addAnnotationPushButton, &QPushButton::clicked, &m_sigmfAnnotation, &QSigMFAnnotation::AddAnnotation);
}

void MainWindow::_InitializeSignalExtConnections()
{
    // SigMF Signal Details Capture Connections
    connect(ui->captureDetailsEnabledCheckBox, &QCheckBox::stateChanged, &m_sigmfCapture, &QSigMFCapture::SetDetsEnabled);
    connect(ui->detailAcqScaledoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetAcqScaleFactor);
    connect(ui->detailsStopCapDateTimeEdit, &QDateTimeEdit::dateTimeChanged, &m_sigmfCapture, &QSigMFCapture::SetStopCapture);
    connect(ui->detailsStartCapDateTimeEdit, &QDateTimeEdit::dateTimeChanged, &m_sigmfCapture, &QSigMFCapture::SetStartCapture);
    connect(ui->detailsAttnDoubleComboBox, &QDoubleSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetAttenuation);
    connect(ui->detailsSrcFileLineEdit, &QLineEdit::textChanged, &m_sigmfCapture, &QSigMFCapture::SetSourceFile);
    connect(ui->detailsAcqBwDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetAcqBandwidth);
    connect(ui->detailsGainDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfCapture, &QSigMFCapture::SetGain);

    // SigMF Signal Details Annotation Connections
    connect(ui->detailsSigRefNumLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetCapDetSigRefNum);
    connect(ui->detailsSnrDbDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetCapDetSnr);
    connect(ui->captureDetailsEnabledCheckBox, &QCheckBox::stateChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetCapDetEnabled);
}

void MainWindow::_InitializeAdbsExtConnections()
{
    // ADSB Annotation Connections
    connect(ui->adsbEnabledCheckBox, &QCheckBox::stateChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAdsbEnabled);
    connect(ui->adsbBinaryPlainTextEdit, &QPlainTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetBinary(ui->adsbBinaryPlainTextEdit->toPlainText());});
    connect(ui->icaAddrDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetIcaAddr);
    connect(ui->adsbMsgTypeComboBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAdsbMsgType);
    connect(ui->downlinkFormatComboBox, &QComboBox::currentIndexChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAdsbDownlinkFrmt);
}

void MainWindow::_InitializeWifiExtConnections()
{
    // Wifi Annotation Connections
    connect(ui->wifiEnableCheckBox, &QCheckBox::stateChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiEnabled);
    connect(ui->wifiStandardTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiStandard(ui->wifiStandardTextEdit->toPlainText());});
    connect(ui->frameTypePhyTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiFrameTypePhy(ui->frameTypePhyTextEdit->toPlainText());});
    connect(ui->wifiChannelSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiChannel);
    connect(ui->wifiStartTimeDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiStartTime);
    connect(ui->wifiStopTimeDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiStopTime);
    connect(ui->wifiFrameDurationDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiFrameDuration);
    connect(ui->wifiMcsSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiMcs);
    connect(ui->wifiMacFrameTypeTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiMacFrameType(ui->wifiMacFrameTypeTextEdit->toPlainText());});
    connect(ui->wifiMacTaTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiMacTxAddr(ui->wifiMacTaTextEdit->toPlainText());});
    connect(ui->wifiMacRaTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiMacRxAddr(ui->wifiMacRaTextEdit->toPlainText());});
    connect(ui->wifiManufacturerTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiTxManf(ui->wifiManufacturerTextEdit->toPlainText());});
    connect(ui->wifiCrcTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiCrc(ui->wifiCrcTextEdit->toPlainText());});
    connect(ui->wifiMacFrameTextEdit, &QTextEdit::textChanged, this, [=] () {m_sigmfAnnotation.SetWifiMacFrame(ui->wifiMacFrameTextEdit->toPlainText());});
    connect(ui->wifiStartPktSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiStartPkt);
    connect(ui->wifiStopPktSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiEndPkt);
    connect(ui->wifiNumSampsSpinBox, &QSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetWifiNumSampsPkt);
}

void MainWindow::_InitializeAntennaExtConnections()
{
    // Antenna Global Connections
    connect(ui->antennaEnableCheckBox, &QAbstractButton::toggled, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaEnabled);
    connect(ui->antennaVertGainPatternSpinBox, &QSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaVertGain);
    connect(ui->antennaVertBeamWidthDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaVertBeamWidth);
    connect(ui->antennaHorzBeamWidthDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaHorizBeamWidth);
    connect(ui->antennaTypeLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaType);
    connect(ui->antennaHighFreqDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaHighFreq);
    connect(ui->antennaModelLineEdit, &QLineEdit::textChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaModel);
    connect(ui->antennaVwsrDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaVswr);
    connect(ui->antennaLowFreqDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaLowFreq);
    connect(ui->antennaGainDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaGain);
    connect(ui->antennaCrossPolDiscSpinBox, &QSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaXPolarDisc);
    connect(ui->antennaHorzGainPatternDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaHorizGain);
    connect(ui->antennaCableLossDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaCableLoss);
    connect(ui->antennaHaglDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaHagl);
    connect(ui->antennaMobileCheckBox, &QCheckBox::stateChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaMobile);
    connect(ui->antennaSteerableCheckBox, &QCheckBox::stateChanged, &m_sigmfGlobal, &QSigMFGlobal::SetAntennaSteerable);


    // Antenna Annotation Connections
    connect(ui->antennaEnableCheckBox, &QAbstractButton::toggled, &m_sigmfAnnotation, &QSigMFAnnotation::SetAntennaEnabled);
    connect(ui->antennaPolarizationLineEdit, &QLineEdit::textChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAntennaPolarization);
    connect(ui->antennaAzimuthDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAntennaAzAng);
    connect(ui->antennaElevationDoubleSpinBox, &QDoubleSpinBox::valueChanged, &m_sigmfAnnotation, &QSigMFAnnotation::SetAntennaElvAng);
}

void MainWindow::_UpdateVariables()
{
    m_metaFilepath = ui->outFilepathLineEdit->text();
    m_metaFilestem = ui->outFilestubLineEdit->text();
}

QByteArray MainWindow::_CreateJson()
{
    QJsonObject globalObj = m_sigmfGlobal.GenerateGlobalJson();
    QJsonArray captureJsonArr = m_sigmfCapture.GenerateCaptureJsonArray();
    QJsonArray annotationJsonArr = m_sigmfAnnotation.GenerateAnnotationJsonArray();

    QJsonObject overallObj;
    overallObj.insert("global", globalObj);
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
