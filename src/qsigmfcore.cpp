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
    : QSigMfBase{parent}
    , m_globalVars()
{
    InitializeGlobalJsonVect({
                                 {"core:sample_rate", "", false},
                                 {"core:author", "", false},
                                 {"core:description", "", false},
                                 {"core:license", "", false},
                                 {"core:metadata_only", "", false},
                                 {"core:number_channels", "", false},
                                 {"core:offset", "", false},
                                 {"core:datatype", "", true},
                                 {"core:hw", "", false},
                                 {"core:version", "", true},
                                 {"core:collection", "", false},
                                 {"core:dataset", "", false},
                                 {"core:data_doi", "", false},
                                 {"core:meta_doi", "", false},
                                 {"core:recorder", "", false},
                                 {"core:sha512", "", false},
                                 {"core:trailing_bytes", "", false},
                                 {"core:geolocation", "", false},
                                 {"core:extensions", "", false}
                             });
    InitializeCaptureJsonVect({
                                  {"core:sample_start", "", true},
                                  {"core:datetime", "", false},
                                  {"core:frequency", "", false},
                                  {"core:global_index", "", false},
                                  {"core:header_bytes", "", false}
                              });
    InitializeAnnotationJsonVect({
                                     {"core:sample_start", "", true},
                                     {"core:sample_count", "", false},
                                     {"core:freq_lower_edge", "", false},
                                     {"core:freq_upper_edge", "", false},
                                     {"core:label", "", false},
                                     {"core:comment", "", false},
                                     {"core:generator", "", false},
                                     {"core:uuid", "", false}
                                 });
}

/*!
 * \brief QSigMfCore::SetSampleRate sets the sample rate.
 * \param sr (double) represents the sample rate of the signal in samples per second.
 */
void QSigMfCore::SetSampleRate(double sr)
{
    m_globalJsonVect.at(0).jsonVal = QString::number(sr);
}

/*!
 * \brief QSigMfCore::SetAuthor sets the author of the file.
 * \param auth (QString) represents a text identifier for the author potentially including
 * name, handle, email, and/or other ID like Amateur Call Sig.
 */
void QSigMfCore::SetAuthor(QString auth)
{
    m_globalJsonVect.at(1).jsonVal = auth;
}

/*!
 * \brief QSigMfCore::SetMetaDoi sets the Metadata file DOI.
 * \param doi (QString) represents the registered DOI (ISO 26324) for a Recording's
 * metadata file.
 */
void QSigMfCore::SetMetaDoi(QString doi)
{
    m_globalJsonVect.at(13).jsonVal = doi;
}

/*!
 * \brief QSigMfCore::SetDataDoi sets the dataset file DOI.
 * \param doi (QString) represents the registered DOI (ISO 26324) for a Recording's
 * dataset file.
 */
void QSigMfCore::SetDataDoi(QString doi)
{
    m_globalJsonVect.at(12).jsonVal = doi;
}

/*!
 * \brief QSigMfCore::SetDescription sets the text description.
 * \param desc (QString) represents a text description of the SigMF Recording.
 */
void QSigMfCore::SetDescription(QString desc)
{
    m_globalJsonVect.at(2).jsonVal = desc;
}

/*!
 * \brief QSigMfCore::SetLicense sets the license.
 * \param l (QString) represents a URL for the license document under which the
 * Recording is offered.
 */
void QSigMfCore::SetLicense(QString l)
{
    m_globalJsonVect.at(3).jsonVal = l;
}

/*!
 * \brief QSigMfCore::SetHardware sets the hardware.
 * \param hw (QString) represents a text description of the hardware used to make
 * the Recording.
 */
void QSigMfCore::SetHardware(QString hw)
{
    m_globalJsonVect.at(8).jsonVal = hw;
}

/*!
 * \brief QSigMfCore::SetMetadataOnly sets if metadata file does not have a dataset.
 * \param isMetaOnly \c true if the metadata file is intentionally distributed without
 * the Dataset.
 */
void QSigMfCore::SetMetadataOnly(bool isMetaOnly)
{
    m_globalJsonVect.at(4).jsonVal = isMetaOnly ? QString("true") : QString("false");
}

/*!
 * \brief QSigMfCore::SetNumberChannels sets the number of channels.
 * \param num (int) represents the number of interleaved channels in the Dataset file,
 * if ommited this is implied to be 1, for multiple channels of IQ data, it is RECOMMENDED
 * to use SigMF Collections instead of num_channels for widest application support.
 */
void QSigMfCore::SetNumberChannels(int num)
{
    m_globalJsonVect.at(5).jsonVal = QString::number(num);
}

/*!
 * \brief QSigMfCore::SetOffset sets the offset
 * \param offset (int) represents the index number of the first sample in the Dataset.
 */
void QSigMfCore::SetOffset(int offset)
{
    m_globalJsonVect.at(6).jsonVal = QString::number(offset);
}

/*!
 * \brief QSigMfCore::SetRecorder sets the recorder.
 * \param rec (QString) represents the name of the software used to make this SigMF
 * Recording.
 */
void QSigMfCore::SetRecorder(QString rec)
{
    m_globalJsonVect.at(14).jsonVal = rec;
}

/*!
 * \brief QSigMfCore::SetTrailingBytes sets the number of trailing bytes.
 * \param num (int) represents the number of bytes to ignore at the end of a Dataset,
 * used ONLY with Non-Conforming Datasets.
 */
void QSigMfCore::SetTrailingBytes(int num)
{
    m_globalJsonVect.at(16).jsonVal = QString::number(num);
}

/*!
 * \brief QSigMfCore::SetVersion sets the version. REQUIRED
 * \param v (QString) represents the verion of the SigMF specification used to create
 * the Metadata file, in the format X
 */
void QSigMfCore::SetVersion(QString v)
{
    m_globalJsonVect.at(9).jsonVal = v;
}

/*!
 * \brief QSigMfCore::SetDataset sets the dataset name.
 * \param str (QString) represents the full filename of the Dataset file this Metadata
 * file describes, used ONLY with Non-Conforming Datasets.
 */
void QSigMfCore::SetDataset(QString str)
{
    m_globalJsonVect.at(11).jsonVal = str;
}

/*!
 * \brief QSigMfCore::SetSha512 sets the SHA512 hash.
 * \param str (QString) represents the SHA512 hash of the Dataset file associated
 * with the SigMF file.
 */
void QSigMfCore::SetSha512(QString str)
{
    m_globalJsonVect.at(15).jsonVal = str;
}

/*!
 * \brief QSigMfCore::SetGeoType sets the Geolocation type.
 * \param gt (QString) represents the type of geolocation value
 */
void QSigMfCore::SetGeoType(QString gt)
{
    m_globalVars.SetGeoType(gt);
}

/*!
 * \brief QSigMfCore::SetLat sets the latitude
 * \param lat (double) the latitude of the geolocation object
 */
void QSigMfCore::SetLat(double lat)
{
    m_globalVars.SetLat(lat);
}

/*!
 * \brief QSigMfCore::SetLon sets the longitude
 * \param lon (double) represents the longitude of the geolocation object.
 */
void QSigMfCore::SetLon(double lon)
{
    m_globalVars.SetLon(lon);
}

/*!
 * \brief QSigMfCore::SetElevation sets the elevation
 * \param elv (double) represents the elevation of the geolocation object.
 */
void QSigMfCore::SetElevation(double elv)
{
    m_globalVars.SetElevation(elv);
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
    m_captureJsonVect.at(0).jsonVal = QString::number(val);
}

/*!
 * \brief QSigMfCore::SetDatetime sets the timestamp of the capture.
 * \param dt (QDateTime) represents the timestamp of the sample index specified
 * by sample_start
 */
void QSigMfCore::SetDatetime(QDateTime dt)
{
    m_captureJsonVect.at(1).jsonVal = dt.toString(Qt::ISODateWithMs);
}

/*!
 * \brief QSigMfCore::SetFrequency sets the center frequency.
 * \param val (double) represents the center frequency of the capture in Hz.
 */
void QSigMfCore::SetFrequency(double val)
{
    m_captureJsonVect.at(2).jsonVal = QString::number(val);
}

/*!
 * \brief QSigMfCore::SetGlobalIndex sets the index of sample_start relative to
 * original sample stream.
 * \param val (int) represents the index of the sample referenced by sample_start
 * relative to an original sample stream.
 */
void QSigMfCore::SetGlobalIndex(int val)
{
    m_captureJsonVect.at(3).jsonVal = QString::number(val);
}

/*!
 * \brief QSigMfCore::SetHeaderBytes sets the number of header bytes.
 * \param val (int) represents the number of bytes preceding a chunk of samples that
 * are not sample data, used for NCDs
 */
void QSigMfCore::SetHeaderBytes(int val)
{
    m_captureJsonVect.at(4).jsonVal = QString::number(val);
}

void QSigMfCore::SetDatetimeEnabled(bool)
{
}

/*!
 * \brief QSigMfCore::SetAnnotSampleStart sets the annotation start sample.
 * \param sr (int) represnets the sample index at which this Segment takes effect.
 */
void QSigMfCore::SetAnnotSampleStart(int sr)
{
    m_annotJsonVect.at(0).jsonVal = QString::number(sr);
}

/*!
 * \brief QSigMfCore::SetSampleCount sets the number of samples.
 * \param sc (int) represents the number of samples that this Segment applies to.
 */
void QSigMfCore::SetSampleCount(int sc)
{
    m_annotJsonVect.at(1).jsonVal = QString::number(sc);
}

/*!
 * \brief QSigMfCore::SetFrequencyLower sets the lower frequency of annotation.
 * \param freq (double) represents the frequency of the lower edge of the feature
 * described by this annotation in Hz
 */
void QSigMfCore::SetFrequencyLower(double freq)
{
    m_annotJsonVect.at(2).jsonVal = QString::number(freq);
}

/*!
 * \brief QSigMfCore::SetFrequencyHigher sets the higher frequency of annotation.
 * \param freq (double) represents the frequency of the higher edge of the feature
 * described by this annotation in Hz
 */
void QSigMfCore::SetFrequencyHigher(double freq)
{
    m_annotJsonVect.at(3).jsonVal = QString::number(freq);
}

/*!
 * \brief QSigMfCore::SetLabel sets the annotation label.
 * \param str (QString) represents a short form human/machine-readable label for the
 * annotation.
 */
void QSigMfCore::SetLabel(QString str)
{
    m_annotJsonVect.at(4).jsonVal = str;
}

/*!
 * \brief QSigMfCore::SetComment sets the annotation comment.
 * \param str (QString) represents a human-readable comment, inteded to be used for
 * longer comments (it is recommened to use 'label' for shorter text).
 */
void QSigMfCore::SetComment(QString str)
{
    m_annotJsonVect.at(5).jsonVal = str;
}

/*!
 * \brief QSigMfCore::SetGenerator sets the annotation generator.
 * \param str (QString) represents a human-readable name of the entity that created this
 * annotation.
 */
void QSigMfCore::SetGenerator(QString str)
{
    m_annotJsonVect.at(6).jsonVal = str;
}

/*!
 * \brief QSigMfCore::SetUuid sets the unique identifier.
 * \param str (QString) represents the RFC-4122 unique identifier.
 */
void QSigMfCore::SetUuid(QString str)
{
    m_annotJsonVect.at(7).jsonVal = str;
}

/*!
 * \brief QSigMfCore::_UpdateDataType updates the datatype string when one of its
 * components is updated.
 * \internal
 */
void QSigMfCore::_UpdateDataType()
{
    m_globalJsonVect.at(7).jsonVal = m_globalVars.GetComplexReal() + m_globalVars.GetDataFormat() + m_globalVars.GetEndianness();
}
