#include "include/qtraceability.h"

QTraceability::QTraceability(QObject *parent)
    : QExtension{{},{},{},parent}
    , m_globalLastMod({})
    , m_globalLastRev({})
    , m_globalOrigin({})
    , m_annotLastMod({})
    , m_annotLastRev({})
{
    SetGlobalExtensionObject("traceability", "1.0.0", false);
    m_globalLastMod.author = "";
}

void QTraceability::SetGlobalLastModAuthor(QString author)
{
    m_globalLastMod.author = author;
    if(_CheckDataChangeStruct(m_globalLastMod)) {
        _UpdateLastModified();
    }
}

void QTraceability::SetGlobalLastModDatetime(QString datetime)
{
    m_globalLastMod.datetime = datetime;
    if(_CheckDataChangeStruct(m_globalLastMod)) {
        _UpdateLastModified();
    }
}

void QTraceability::SetGlobalLastRevAuthor(QString author)
{
    m_globalLastRev.author = author;
    if(_CheckDataChangeStruct(m_globalLastRev)) {
        _UpdateLastReviewed();
    }
}

void QTraceability::SetGlobalLastRevDatetime(QString datetime)
{
    m_globalLastRev.datetime = datetime;
    if(_CheckDataChangeStruct(m_globalLastRev)) {
        _UpdateLastReviewed();
    }
}

void QTraceability::SetRevision(int rev)
{
    m_globalJsonMap.insert_or_assign("revision", QJsonObject{{"traceability:revision", rev}});
}

void QTraceability::SetOriginAccount(QString account)
{
    m_globalOrigin.account = account;
    if(_CheckOriginStruct(m_globalOrigin)) {
        _UpdateOrigin();
    }
}

void QTraceability::SetOriginContainer(QString container)
{
    m_globalOrigin.container = container;
    if(_CheckOriginStruct(m_globalOrigin)) {
        _UpdateOrigin();
    }
}

void QTraceability::SetOriginFilepath(QString filepath)
{
    m_globalOrigin.file_path = filepath;
    if(_CheckOriginStruct(m_globalOrigin)) {
        _UpdateOrigin();
    }
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

void QTraceability::_UpdateLastModified()
{
    QJsonObject tmp, obj;
    tmp.insert("datetime", m_globalLastMod.datetime);
    if(m_globalLastMod.author.compare("")) {
        tmp.insert("author", m_globalLastMod.author);
    }
    obj.insert("traceability:last_modified", tmp);
    m_globalJsonMap.insert_or_assign("last_modified", obj);
}

void QTraceability::_UpdateLastReviewed()
{
    QJsonObject tmp, obj;
    tmp.insert("datetime", m_globalLastRev.datetime);
    if(m_globalLastRev.author.compare("")) {
        tmp.insert("author", m_globalLastRev.author);
    }
    obj.insert("traceability:last_reviewed", tmp);
    m_globalJsonMap.insert_or_assign("last_reviewed", obj);
}

void QTraceability::_UpdateOrigin()
{
    QJsonObject tmp, obj;
    tmp.insert("file_path", m_globalOrigin.file_path);
    if(m_globalOrigin.account.compare("")) {
        tmp.insert("account", m_globalOrigin.account);
    }
    if(m_globalOrigin.container.compare("")) {
        tmp.insert("container", m_globalOrigin.container);
    }
    obj.insert("traceability:origin", tmp);
    m_globalJsonMap.insert_or_assign("origin", obj);
}
