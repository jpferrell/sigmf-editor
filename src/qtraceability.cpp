#include "include/qtraceability.h"

QTraceability::QTraceability(QObject *parent)
    : QExtension{parent}
    , m_globalLastMod({})
    , m_globalLastRev({})
    , m_globalOrigin({})
    , m_annotLastMod({})
    , m_annotLastRev({})
{
    InitializeGlobalJsonVect({
                                 {"traceability:last_modified", "", false},
                                 {"traceability:last_reviewed", "", false},
                                 {"traceability:revision", "", false},
                                 {"traceability:origin", "", false}
                             });
    InitializeCaptureJsonVect({
                                  {"traceability:last_modified", "", false},
                                  {"traceability:last_reviewed", "", false}
                              });
    SetGlobalExtensionObject("traceability", "1.0.0", false);
    m_globalLastMod.author = "";
}

QJsonObject QTraceability::GetGlobalLastMod()
{
    QJsonObject retObj;
    if (_CheckDataChangeStruct(m_globalLastMod)) {
        retObj.insert("datetime", m_globalLastMod.datetime);
        if (QString::compare(m_globalLastMod.author, "")) {
            retObj.insert("author", m_globalLastMod.author);
        }
    }
    return retObj;
}

QJsonObject QTraceability::GetGlobalLastRev()
{
    QJsonObject retObj;
    if (_CheckDataChangeStruct(m_globalLastRev)) {
        retObj.insert("datetime", m_globalLastRev.datetime);
        if (QString::compare(m_globalLastRev.author, "")) {
            retObj.insert("author", m_globalLastRev.author);
        }
    }
    return retObj;
}

QString QTraceability::GetGlobalRevision()
{
    return m_globalJsonVect.at(2).jsonVal;
}

QJsonObject QTraceability::GetGlobalOrigin()
{
    QJsonObject retObj;
    if (_CheckOriginStruct(m_globalOrigin)) {
        retObj.insert("file_path", m_globalOrigin.file_path);
        if (QString::compare(m_globalOrigin.account, "")) {
            retObj.insert("account", m_globalOrigin.account);
        }
        if (QString::compare(m_globalOrigin.container, "")) {
            retObj.insert("container", m_globalOrigin.container);
        }
    }

    return retObj;
}

QJsonObject QTraceability::GetAnnotLastMod()
{
    QJsonObject retObj;
    if (_CheckDataChangeStruct(m_annotLastMod)) {
        retObj.insert("datetime", m_annotLastMod.datetime);
        if (QString::compare(m_annotLastMod.author, "")) {
            retObj.insert("author", m_annotLastMod.author);
        }
    }
    return retObj;
}

QJsonObject QTraceability::GetAnnotLastRev()
{
    QJsonObject retObj;
    if (_CheckDataChangeStruct(m_annotLastRev)) {
        retObj.insert("datetime", m_annotLastRev.datetime);
        if (QString::compare(m_annotLastRev.author, "")) {
            retObj.insert("author", m_annotLastRev.author);
        }
    }
    return retObj;
}

void QTraceability::SetGlobalLastModAuthor(QString author)
{
    m_globalLastMod.author = author;
}

void QTraceability::SetGlobalLastModDatetime(QString datetime)
{
    m_globalLastMod.datetime = datetime;
}

void QTraceability::SetGlobalLastRevAuthor(QString author)
{
    m_globalLastRev.author = author;
}

void QTraceability::SetGlobalLastRevDatetime(QString datetime)
{
    m_globalLastRev.datetime = datetime;
}

void QTraceability::SetRevision(int rev)
{
    m_globalJsonVect.at(2).jsonVal = QString::number(rev);
}

void QTraceability::SetOriginAccount(QString account)
{
    m_globalOrigin.account = account;
}

void QTraceability::SetOriginContainer(QString container)
{
    m_globalOrigin.container = container;
}

void QTraceability::SetOriginFilepath(QString filepath)
{
    m_globalOrigin.file_path = filepath;
}

void QTraceability::SetAnnotLastModAuthor(QString author)
{
    m_annotLastMod.author = author;
}

void QTraceability::SetAnnotLastModDatetime(QString datetime)
{
    m_annotLastMod.datetime = datetime;
}

void QTraceability::SetAnnotLastRevAuthor(QString author)
{
    m_annotLastRev.author = author;
}

void QTraceability::SetAnnotLastRevDatetime(QString datetime)
{
    m_annotLastRev.datetime = datetime;
}

bool QTraceability::_CheckDataChangeStruct(dataChange_t in)
{
    return QString::compare(in.datetime, "") ? true : false;
}

bool QTraceability::_CheckOriginStruct(origin_t in)
{
    return QString::compare(in.file_path, "") ? true : false;
}
