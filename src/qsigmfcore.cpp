#include "include/qsigmfcore.h"

/*!
 * \class QSigMFCore
 * \since v0.0.1
 *
 * \brief The QSigMfCore class represents the JSON key/values in the core specification as can
 * be found at sigmf.org
 */

/*!
 * \brief QSigMfCore::QSigMfCore constructs the QSigMfCore class with the JSON key/values in the
 * core specification.
 * \param parent (QObject *)
 */
QSigMfCore::QSigMfCore(QObject *parent)
    : QSigMfBase{
          {"version"}, // Global keys
          {"sample_start"}, // capture keys
          {"sample_start"}, // annotation keys
          parent}
    , m_globalVars()
{
}

/*!
 * \brief QSigMfCore::SetSampleRate sets the sample rate.
 * \param sr (double) represents the sample rate of the signal in samples per second.
 */
void QSigMfCore::SetSampleRate(double sr)
{
    m_globalJsonMap.insert_or_assign("sample_rate", QJsonObject{{"core:sample_rate", sr}});
}

/*!
 * \brief QSigMfCore::SetAuthor sets the author of the file.
 * \param auth (QString) represents a text identifier for the author potentially including
 * name, handle, email, and/or other ID like Amateur Call Sig.
 */
void QSigMfCore::SetAuthor(QString auth)
{
    m_globalJsonMap.insert_or_assign("author", QJsonObject{{"core:author", auth}});
}

/*!
 * \brief QSigMfCore::SetMetaDoi sets the Metadata file DOI.
 * \param doi (QString) represents the registered DOI (ISO 26324) for a Recording's
 * metadata file.
 */
void QSigMfCore::SetMetaDoi(QString doi)
{
    m_globalJsonMap.insert_or_assign("meta_doi", QJsonObject{{"core:meta_doi", doi}});
}

/*!
 * \brief QSigMfCore::SetDataDoi sets the dataset file DOI.
 * \param doi (QString) represents the registered DOI (ISO 26324) for a Recording's
 * dataset file.
 */
void QSigMfCore::SetDataDoi(QString doi)
{
    m_globalJsonMap.insert_or_assign("meta_doi", QJsonObject{{"core:data_doi", doi}});
}

/*!
 * \brief QSigMfCore::SetDescription sets the text description.
 * \param desc (QString) represents a text description of the SigMF Recording.
 */
void QSigMfCore::SetDescription(QString desc)
{
    m_globalJsonMap.insert_or_assign("description", QJsonObject{{"core:description", desc}});
}

/*!
 * \brief QSigMfCore::SetLicense sets the license.
 * \param l (QString) represents a URL for the license document under which the
 * Recording is offered.
 */
void QSigMfCore::SetLicense(QString l)
{
    m_globalJsonMap.insert_or_assign("license", QJsonObject{{"core:license", l}});
}

/*!
 * \brief QSigMfCore::SetHardware sets the hardware.
 * \param hw (QString) represents a text description of the hardware used to make
 * the Recording.
 */
void QSigMfCore::SetHardware(QString hw)
{
    m_globalJsonMap.insert_or_assign("hw", QJsonObject{{"core:hw", hw}});
}

/*!
 * \brief QSigMfCore::SetMetadataOnly sets if metadata file does not have a dataset.
 * \param isMetaOnly \c true if the metadata file is intentionally distributed without
 * the Dataset.
 */
void QSigMfCore::SetMetadataOnly(bool isMetaOnly)
{
    QString metaStr = isMetaOnly ? QString("true") : QString("false");
    m_globalJsonMap.insert_or_assign("metadata_only", QJsonObject{{"core:metadata_only", metaStr}});
}

/*!
 * \brief QSigMfCore::SetNumberChannels sets the number of channels.
 * \param num (int) represents the number of interleaved channels in the Dataset file,
 * if ommited this is implied to be 1, for multiple channels of IQ data, it is RECOMMENDED
 * to use SigMF Collections instead of num_channels for widest application support.
 */
void QSigMfCore::SetNumberChannels(int num)
{
    m_globalJsonMap.insert_or_assign("num_channels", QJsonObject{{"core:num_channels", num}});
}

/*!
 * \brief QSigMfCore::SetOffset sets the offset
 * \param offset (int) represents the index number of the first sample in the Dataset.
 */
void QSigMfCore::SetOffset(int offset)
{
    m_globalJsonMap.insert_or_assign("offset", QJsonObject{{"core:offset", offset}});
}

/*!
 * \brief QSigMfCore::SetRecorder sets the recorder.
 * \param rec (QString) represents the name of the software used to make this SigMF
 * Recording.
 */
void QSigMfCore::SetRecorder(QString rec)
{
    m_globalJsonMap.insert_or_assign("recorder", QJsonObject{{"core:recorder", rec}});
}

/*!
 * \brief QSigMfCore::SetTrailingBytes sets the number of trailing bytes.
 * \param num (int) represents the number of bytes to ignore at the end of a Dataset,
 * used ONLY with Non-Conforming Datasets.
 */
void QSigMfCore::SetTrailingBytes(int num)
{
    m_globalJsonMap.insert_or_assign("trailing_bytes", QJsonObject{{"core:trailing_bytes", num}});
}

/*!
 * \brief QSigMfCore::SetVersion sets the version. REQUIRED
 * \param v (QString) represents the verion of the SigMF specification used to create
 * the Metadata file, in the format X
 */
void QSigMfCore::SetVersion(QString v)
{
    m_globalJsonMap.insert_or_assign("version", QJsonObject{{"core:version", v}});
}

/*!
 * \brief QSigMfCore::SetDataset sets the dataset name.
 * \param str (QString) represents the full filename of the Dataset file this Metadata
 * file describes, used ONLY with Non-Conforming Datasets.
 */
void QSigMfCore::SetDataset(QString str)
{
    m_globalJsonMap.insert_or_assign("dataset", QJsonObject{{"core:dataset", str}});
}

/*!
 * \brief QSigMfCore::SetSha512 sets the SHA512 hash.
 * \param str (QString) represents the SHA512 hash of the Dataset file associated
 * with the SigMF file.
 */
void QSigMfCore::SetSha512(QString str)
{
    m_globalJsonMap.insert_or_assign("sha512", QJsonObject{{"core:sha512", str}});
}

/*!
 * \brief QSigMfCore::SetGeoType sets the Geolocation type.
 * \param gt (QString) represents the type of geolocation value
 */
void QSigMfCore::SetGeoType(QString gt)
{
    m_globalVars.SetGeoType(gt);
    // need to have an update geojson here if valid
    if (_CheckValidGeo()) {
        _UpdateGeo();
    }
}

/*!
 * \brief QSigMfCore::SetLat sets the latitude
 * \param lat (double) the latitude of the geolocation object
 */
void QSigMfCore::SetLat(double lat)
{
    m_globalVars.SetLat(lat);
    if (_CheckValidGeo()) {
        _UpdateGeo();
    }
}

/*!
 * \brief QSigMfCore::SetLon sets the longitude
 * \param lon (double) represents the longitude of the geolocation object.
 */
void QSigMfCore::SetLon(double lon)
{
    m_globalVars.SetLon(lon);
    if (_CheckValidGeo()) {
        _UpdateGeo();
    }
}

/*!
 * \brief QSigMfCore::SetElevation sets the elevation
 * \param elv (double) represents the elevation of the geolocation object.
 */
void QSigMfCore::SetElevation(double elv)
{
    m_globalVars.SetElevation(elv);
    if (_CheckValidGeo()) {
        _UpdateGeo();
    }
}

/*!
 * \brief QSigMfCore::SetComplex sets whether the data is complex or not.
 * \param str (const QString &) "Complex" if data is complex
 */
void QSigMfCore::SetComplex(const QString &str)
{
    bool isCplx = str.compare("Complex") ? false : true;
    m_globalVars.SetComplex(isCplx);
    _UpdateDataType();
}

/*!
 * \brief QSigMfCore::SetDataFormat sets the data format
 * \param str (QString) represents the format of the signal data. Of format
 * <f/i/u><64/32/16/8>.
 */
void QSigMfCore::SetDataFormat(QString str)
{
    m_globalVars.SetDataFormat(str+"_");
    _UpdateDataType();
}

/*!
 * \brief QSigMfCore::SetEndianness sets the endianness of the data.
 * \param str (QString) represents the endianness of the signal data.
 */
void QSigMfCore::SetEndianness(QString str)
{
    QString end = str.compare("Big Endian") ? "le" : "be";
    m_globalVars.SetEndianness(end);
    _UpdateDataType();
}

/*!
 * \brief QSigMfCore::SetSampleStart sets the first sample. REQUIRED
 * \param val (int) represents the index of the first sample of this chunk.
 */
void QSigMfCore::SetSampleStart(int val)
{
    m_captureJsonMap.insert_or_assign("sample_start", QJsonObject{{"core:sample_start", val}});
}

/*!
 * \brief QSigMfCore::SetDatetime sets the timestamp of the capture.
 * \param dt (QDateTime) represents the timestamp of the sample index specified
 * by sample_start
 */
void QSigMfCore::SetDatetime(QDateTime dt)
{
    m_captureJsonMap.insert_or_assign("datetime", QJsonObject{{"core:datetime", dt.toString(Qt::ISODateWithMs)}});
}

/*!
 * \brief QSigMfCore::SetFrequency sets the center frequency.
 * \param val (double) represents the center frequency of the capture in Hz.
 */
void QSigMfCore::SetFrequency(double val)
{
    m_captureJsonMap.insert_or_assign("frequency", QJsonObject{{"core:frequency", val}});
}

/*!
 * \brief QSigMfCore::SetGlobalIndex sets the index of sample_start relative to
 * original sample stream.
 * \param val (int) represents the index of the sample referenced by sample_start
 * relative to an original sample stream.
 */
void QSigMfCore::SetGlobalIndex(int val)
{
    m_captureJsonMap.insert_or_assign("global_index", QJsonObject{{"core:global_index", val}});
}

/*!
 * \brief QSigMfCore::SetHeaderBytes sets the number of header bytes.
 * \param val (int) represents the number of bytes preceding a chunk of samples that
 * are not sample data, used for NCDs
 */
void QSigMfCore::SetHeaderBytes(int val)
{
    m_captureJsonMap.insert_or_assign("header_bytes", QJsonObject{{"core:header_bytes", val}});
}

void QSigMfCore::SetDatetimeEnabled(bool)
{
}

/*!
 * \brief QSigMfCore::SetAnnotSampleStart sets the annotation start sample.
 * \param sr (int) represnets the sample index at which this Segment takes effect.
 */
void QSigMfCore::SetAnnotSampleStart(int val)
{
    m_annotJsonMap.insert_or_assign("sample_start", QJsonObject{{"core:sample_start", val}});
}

/*!
 * \brief QSigMfCore::SetSampleCount sets the number of samples.
 * \param sc (int) represents the number of samples that this Segment applies to.
 */
void QSigMfCore::SetSampleCount(int sc)
{
    m_annotJsonMap.insert_or_assign("sample_count", QJsonObject{{"core:sample_count", sc}});
}

/*!
 * \brief QSigMfCore::SetFrequencyLower sets the lower frequency of annotation.
 * \param freq (double) represents the frequency of the lower edge of the feature
 * described by this annotation in Hz
 */
void QSigMfCore::SetFrequencyLower(double freq)
{
    m_annotJsonMap.insert_or_assign("freq_lower_edge", QJsonObject{{"core:freq_lower_edge", freq}});
}

/*!
 * \brief QSigMfCore::SetFrequencyHigher sets the higher frequency of annotation.
 * \param freq (double) represents the frequency of the higher edge of the feature
 * described by this annotation in Hz
 */
void QSigMfCore::SetFrequencyHigher(double freq)
{
    m_annotJsonMap.insert_or_assign("freq_upper_edge", QJsonObject{{"core:freq_upper_edge", freq}});
}

/*!
 * \brief QSigMfCore::SetLabel sets the annotation label.
 * \param str (QString) represents a short form human/machine-readable label for the
 * annotation.
 */
void QSigMfCore::SetLabel(QString str)
{
    m_annotJsonMap.insert_or_assign("label", QJsonObject{{"core:label", str}});
}

/*!
 * \brief QSigMfCore::SetComment sets the annotation comment.
 * \param str (QString) represents a human-readable comment, inteded to be used for
 * longer comments (it is recommened to use 'label' for shorter text).
 */
void QSigMfCore::SetComment(QString str)
{
    m_annotJsonMap.insert_or_assign("comment", QJsonObject{{"core:comment", str}});
}

/*!
 * \brief QSigMfCore::SetGenerator sets the annotation generator.
 * \param str (QString) represents a human-readable name of the entity that created this
 * annotation.
 */
void QSigMfCore::SetGenerator(QString str)
{
    m_annotJsonMap.insert_or_assign("generator", QJsonObject{{"core:generator", str}});
}

/*!
 * \brief QSigMfCore::SetUuid sets the unique identifier.
 * \param str (QString) represents the RFC-4122 unique identifier.
 */
void QSigMfCore::SetUuid(QString str)
{
    m_annotJsonMap.insert_or_assign("uuid", QJsonObject{{"core:uuid", str}});
}

/*!
 * \brief QSigMfCore::_UpdateDataType updates the datatype string when one of its
 * components is updated.
 * \internal
 */
void QSigMfCore::_UpdateDataType()
{
    m_globalJsonMap.insert_or_assign("datatype", QJsonObject{{"core:datatype", m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness()}});
}

bool QSigMfCore::_CheckValidGeo()
{
    qDebug() << "in _CheckValidGeo";
    //return ((m_globalJsonMap.find("longitude") != m_globalJsonMap.end()) && (m_globalJsonMap.find("latitude") != m_globalJsonMap.end())) ? true : false;
    return ((!m_globalVars.GetGeoLat().compare("")) && (!m_globalVars.GetGeoLon().compare(""))) ? true : false;
}

void QSigMfCore::_UpdateGeo()
{
    qDebug() << "in _UpdateGeo";
    m_globalJsonMap.insert_or_assign("geolocation", QJsonObject{{"type", m_globalVars.GetGeoType()}, {"coordinates", QJsonArray{m_globalVars.GetGeoLat(), m_globalVars.GetGeoLon(), m_globalVars.GetGeoElv()}}});
}
