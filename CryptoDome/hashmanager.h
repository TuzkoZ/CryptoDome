#ifndef HASHMANAGER_H
#define HASHMANAGER_H

#include <QCryptographicHash>
#include <QString>
#include <QFile>

class HashManager
{
public:
    HashManager();
    QString getHash_MD4(QString filePath);
    QString getHash_MD5(QString filePath);
    QString getHash_SHA1(QString filePath);
    QString getHash_SHA224(QString filePath);
    QString getHash_SHA256(QString filePath);
    QString getHash_SHA384(QString filePath);
    QString getHash_SHA512(QString filePath);
    QString getHash_SHA3_224_R(QString filePath);
    QString getHash_SHA3_256_R(QString filePath);
    QString getHash_SHA3_384_R(QString filePath);
    QString getHash_SHA3_512_R(QString filePath);
    QString getHash_SHA3_224_Keccak(QString filePath);
    QString getHash_SHA3_256_Keccak(QString filePath);
    QString getHash_SHA3_384_Keccak(QString filePath);
    QString getHash_SHA3_512_Keccak(QString filePath);
};

#endif // HASHMANAGER_H
