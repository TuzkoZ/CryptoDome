#ifndef STORAGEMNGR_H
#define STORAGEMNGR_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <cryptmanager.h>
#include <passrecord.h>
#include <vector>

struct StorageInfo
{
    QString storagePath;
    QString masterKey;
};

class StorageMngr
{
public:
    StorageMngr(QString storagePath, QString masterKey);
    ~StorageMngr();
    void setStoragePath(QString storagePath);
    void setMasterKey(QString masterKey);
    void createStorage();
    void readToStorage();
    void syncStorage();
    void saveRecordInfo(QString name, QString URL, QString login, QString password, QString description);
    void addRecord(QString name, QString URL, QString login, QString password, QString description);
    void delRecord(QString name);

    vector<PassRecord> storage;

private:
    StorageInfo *storageInfo;
    QJsonDocument storageDocument;
};

#endif // STORAGEMNGR_H
