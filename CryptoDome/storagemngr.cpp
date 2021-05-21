#include "storagemngr.h"

StorageMngr::StorageMngr(QString storagePath, QString masterKey)
{
    storageInfo = new StorageInfo();
    storageInfo->storagePath = storagePath;
    storageInfo->masterKey = masterKey;

    readToStorage();

    qDebug() << storageInfo->storagePath;
    qDebug() << storageInfo->masterKey;
}

StorageMngr::~StorageMngr()
{
    delete storageInfo;
    syncStorage();
}

void StorageMngr::setMasterKey(QString masterKey)
{
    this->storageInfo->masterKey = masterKey;
}

void StorageMngr::setStoragePath(QString storagePath)
{
    this->storageInfo->storagePath = storagePath;
}

void StorageMngr::createStorage()
{
    if(!storageInfo->storagePath.isEmpty())
    {
        QString filePath = storageInfo->storagePath + "_";

        QJsonObject versionObject;
        versionObject["name"] = "CryptoDome";
        versionObject["version"] = "1.14";
        versionObject["Developer"] = "TuzkoZ";

        QJsonObject testPassObject;
        testPassObject["name"] = "Test pass object";
        testPassObject["URL"] = "localhost";
        testPassObject["login"] = "Test login";
        testPassObject["password"] = "Test password";
        testPassObject["description"] = "Test description";

        QJsonArray jsonArray;

        jsonArray.append(versionObject);
        jsonArray.append(testPassObject);

        QJsonObject jObj;
        jObj["items"] = jsonArray;


        QFile jsonFile(filePath);
        if(jsonFile.open(QIODevice::WriteOnly))
        {
            jsonFile.write(QJsonDocument(jObj).toJson());
            jsonFile.close();
        }

        CryptManager *crypter = new CryptManager();
        crypter->encryptFile_AES_256(filePath.toStdString(), filePath.toStdString().substr(0, filePath.length() - 1) , storageInfo->masterKey.toStdString(), cryptMode::CFB);
        QFile::remove(filePath);
        //delete crypter;
    }
}

void StorageMngr::readToStorage()
{
    QString filePath = storageInfo->storagePath;
    qDebug() << filePath;
    CryptManager *crypter = new CryptManager();
    crypter->decryptFile_AES_256(filePath.toStdString(), (filePath + "_").toStdString() , storageInfo->masterKey.toStdString(), cryptMode::CFB);

    QFile jsonFile(filePath + "_");
    if(jsonFile.open(QIODevice::ReadOnly))
    {
        storageDocument = QJsonDocument::fromJson(jsonFile.readAll());
        qDebug() << storageDocument;
        jsonFile.close();

        QJsonObject jsonObject = storageDocument.object();
        QJsonArray jsonArray = storageDocument["items"].toArray();

        int count = 0;

        foreach (const QJsonValue & value, jsonArray)
        {
            if(count != 0)
            {
                PassRecord record(value["name"].toString(), value["URL"].toString(), value["login"].toString(), value["password"].toString(), value["description"].toString());
                storage.push_back(record);
            }
            count++;
        }

        qDebug() << storage.size();

    }

    QFile::remove((filePath + "_"));
    //delete crypter;
}

void StorageMngr::syncStorage()
{
    QString filePath = storageInfo->storagePath + "_";

    QJsonObject versionObject;
    versionObject["name"] = "CryptoDome";
    versionObject["version"] = "1.14";
    versionObject["Developer"] = "TuzkoZ";

    QJsonArray jsonArray;
    jsonArray.append(versionObject);

    for(int i = 0; i < storage.size(); i++)
    {
        QJsonObject testPassObject;
        testPassObject["name"] = storage.at(i).getName();
        testPassObject["URL"] = storage.at(i).getURL();
        testPassObject["login"] = storage.at(i).getLogin();
        testPassObject["password"] = storage.at(i).getPassword();
        testPassObject["description"] = storage.at(i).getDescription();

        jsonArray.append(testPassObject);
    }


    QJsonObject jObj;
    jObj["items"] = jsonArray;


    QFile jsonFile(filePath);
    if(jsonFile.open(QIODevice::WriteOnly))
    {
        jsonFile.write(QJsonDocument(jObj).toJson());
        jsonFile.close();
    }

    CryptManager *crypter = new CryptManager();
    crypter->encryptFile_AES_256(filePath.toStdString(), filePath.toStdString().substr(0, filePath.length() - 1) , storageInfo->masterKey.toStdString(), cryptMode::CFB);
    QFile::remove(filePath);
}

void StorageMngr::saveRecordInfo(QString name, QString URL, QString login, QString password, QString description)
{
    for(int i = 0; i < storage.size(); i++)
    {
        if(storage.at(i).getName() == name)
        {
            storage.at(i).setName(name);
            storage.at(i).setURL(URL);
            storage.at(i).setLogin(login);
            storage.at(i).setPassword(password);
            storage.at(i).setDescription(description);
        }
    }

    syncStorage();

}

void StorageMngr::addRecord(QString name, QString URL, QString login, QString password, QString description)
{
    PassRecord record(name, URL, login, password, description);
    storage.push_back(record);
    syncStorage();
}

void StorageMngr::delRecord(QString name)
{
    auto iter = storage.begin();
    while(iter != storage.end())
    {
        if(iter->getName() == name)
        {
            storage.erase(iter);
        }
        iter++;
    }

    syncStorage();
}
