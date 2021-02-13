#include "hashmanager.h"

HashManager::HashManager()
{

}

QString HashManager::getHash_MD4(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash md4Generator(QCryptographicHash::Md4);

    if(sourceFile.open(QFile::ReadOnly))
    {
        md4Generator.addData(sourceFile.readAll());
    }

    return md4Generator.result().toHex();
}

QString HashManager::getHash_MD5(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash md5Generator(QCryptographicHash::Md5);

    if(sourceFile.open(QFile::ReadOnly))
    {
        md5Generator.addData(sourceFile.readAll());
    }

    return md5Generator.result().toHex();
}

QString HashManager::getHash_SHA1(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha1);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA224(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha224);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA256(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha256);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA384(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha384);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA512(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha512);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_224_R(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::RealSha3_224);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_256_R(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::RealSha3_256);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_384_R(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::RealSha3_384);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_512_R(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::RealSha3_512);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_224_Keccak(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha3_224);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_256_Keccak(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha3_256);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_384_Keccak(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha3_384);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}

QString HashManager::getHash_SHA3_512_Keccak(QString filePath)
{
    QFile sourceFile(filePath);
    QCryptographicHash sha1Generator(QCryptographicHash::Sha3_512);

    if(sourceFile.open(QFile::ReadOnly))
    {
        sha1Generator.addData(sourceFile.readAll());
    }

    return sha1Generator.result().toHex();
}
