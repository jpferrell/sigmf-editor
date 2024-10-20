#ifndef QTRACEABILITY_H
#define QTRACEABILITY_H

#include <QObject>

#include "qextension.h"
#include "qsigmftypes.h"

class QTraceability : public QExtension
{
    Q_OBJECT
public:
    explicit QTraceability(QObject *parent = nullptr);

    sigmfVector_t GetGlobalValues();

    QJsonObject GetGlobalLastMod();
    QJsonObject GetGlobalLastRev();
    QString GetGlobalRevision();
    QJsonObject GetGlobalOrigin();
    QJsonObject GetAnnotLastMod();
    QJsonObject GetAnnotLastRev();

signals:

public slots:

    void SetGlobalLastModAuthor(QString author);
    void SetGlobalLastModDatetime(QString datetime);
    void SetGlobalLastRevAuthor(QString author);
    void SetGlobalLastRevDatetime(QString datetime);
    void SetRevision(int rev);
    void SetOriginAccount(QString account);
    void SetOriginContainer(QString container);
    void SetOriginFilepath(QString filepath);
    void SetAnnotLastModAuthor(QString author);
    void SetAnnotLastModDatetime(QString datetime);
    void SetAnnotLastRevAuthor(QString author);
    void SetAnnotLastRevDatetime(QString datetime);


protected:

private:

    dataChange_t m_globalLastMod;
    dataChange_t m_globalLastRev;
    origin_t m_globalOrigin;
    dataChange_t m_annotLastMod;
    dataChange_t m_annotLastRev;

    bool _CheckDataChangeStruct(dataChange_t);
    bool _CheckOriginStruct(origin_t);
};

#endif // QTRACEABILITY_H
