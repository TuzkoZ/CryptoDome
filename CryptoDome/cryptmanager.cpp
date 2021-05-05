#include "cryptmanager.h"

CryptManager::CryptManager()
{

}

void CryptManager::encryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode)
{
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH]; //КЛЮЧ
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; //IV

    if(sKey.length() < CryptoPP::AES::DEFAULT_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*');
    }

    memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    CryptoPP::AutoSeededRandomPool rng{};
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);
        ifstream inFile(filePath_In, ios::binary);
        ofstream outFile(filePath_Out, ios::binary);

        CryptoPP::FileSink file(filePath_Out.c_str());
        CryptoPP::ArraySource as(iv, CryptoPP::AES::BLOCKSIZE, true, new CryptoPP::Redirector(file));

        CryptoPP::FileSource{inFile, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::Redirector(file)}};
    }
    }
}

void CryptManager::encryptFile_AES_128_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath)
{
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH]; //КЛЮЧ
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; //IV

    if(sKey.length() < CryptoPP::AES::DEFAULT_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*');
    }

    hashManager = new HashManager();
    string hashFile = hashManager->getHash_MD5(QString::fromLocal8Bit(keyFilePath.c_str())).toStdString();

    string newKey;
    for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
    {
        newKey = newKey + char((sKey[i] & hashFile[i]));
    }

    qDebug() << QString::fromStdString(newKey);

    memcpy(key, newKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    CryptoPP::AutoSeededRandomPool rng{};
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);
        ifstream inFile(filePath_In, ios::binary);
        ofstream outFile(filePath_Out, ios::binary);

        CryptoPP::FileSink file(filePath_Out.c_str());
        CryptoPP::ArraySource as(iv, CryptoPP::AES::BLOCKSIZE, true, new CryptoPP::Redirector(file));

        CryptoPP::FileSource{inFile, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::Redirector(file)}};
    }
    }
}

void CryptManager::decryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode)
{
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH]; //КЛЮЧ

    if(sKey.length() < CryptoPP::AES::DEFAULT_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*');
    }
    memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::FileSource fileSource(filePath_In.c_str(), false);

    CryptoPP::ArraySink as(iv, iv.size());
    fileSource.Attach(new CryptoPP::Redirector(as));
    fileSource.Pump(CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decipher(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

        CryptoPP::ByteQueue queue;
        fileSource.Detach(new CryptoPP::StreamTransformationFilter(decipher, new CryptoPP::Redirector(queue)));
        fileSource.PumpAll();

        CryptoPP::FileSink fileSink(filePath_Out.c_str());
        queue.TransferTo(fileSink);
    }
    }
}

void CryptManager::decryptFile_AES_128_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath)
{
    CryptoPP::byte readyKey[CryptoPP::AES::DEFAULT_KEYLENGTH]; //Готовый ключ
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH]; //КЛЮЧ

    if(sKey.length() < CryptoPP::AES::DEFAULT_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*');
    }

    hashManager = new HashManager();
    string hashFile = hashManager->getHash_MD5(QString::fromLocal8Bit(keyFilePath.c_str())).toStdString();

    string newKey;
    for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
    {
        newKey = newKey + char((sKey[i] & hashFile[i]));
    }

    qDebug() << QString::fromStdString(newKey);

    memcpy(key, newKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::FileSource fileSource(filePath_In.c_str(), false);

    CryptoPP::ArraySink as(iv, iv.size());
    fileSource.Attach(new CryptoPP::Redirector(as));
    fileSource.Pump(CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decipher(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

        CryptoPP::ByteQueue queue;
        fileSource.Detach(new CryptoPP::StreamTransformationFilter(decipher, new CryptoPP::Redirector(queue)));
        fileSource.PumpAll();

        CryptoPP::FileSink fileSink(filePath_Out.c_str());
        queue.TransferTo(fileSink);
    }
    }
}

void CryptManager::encryptFile_AES_256(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode)
{
    CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH]; //КЛЮЧ
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; //IV

    if(sKey.length() < CryptoPP::AES::MAX_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::MAX_KEYLENGTH - sKey.size(), '*');
    }
    memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);

    CryptoPP::AutoSeededRandomPool rng{};
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher(key, CryptoPP::AES::MAX_KEYLENGTH, iv);
        ifstream inFile(filePath_In, ios::binary);
        ofstream outFile(filePath_Out, ios::binary);

        CryptoPP::FileSink file(filePath_Out.c_str());
        CryptoPP::ArraySource as(iv, CryptoPP::AES::BLOCKSIZE, true, new CryptoPP::Redirector(file));

        CryptoPP::FileSource{inFile, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::Redirector(file)}};
    }
    }
}

void CryptManager::encryptFile_AES_256_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath)
{
    CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH]; //КЛЮЧ
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; //IV

    if(sKey.length() < CryptoPP::AES::MAX_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::MAX_KEYLENGTH - sKey.size(), '*');
    }

    hashManager = new HashManager();
    string hashFile = hashManager->getHash_MD5(QString::fromLocal8Bit(keyFilePath.c_str())).toStdString();

    string newKey;
    for(int i = 0; i < CryptoPP::AES::MAX_KEYLENGTH; i++)
    {
        newKey = newKey + char((sKey[i] & hashFile[i]));
    }

    memcpy(key, newKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);

    CryptoPP::AutoSeededRandomPool rng{};
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher(key, CryptoPP::AES::MAX_KEYLENGTH, iv);
        ifstream inFile(filePath_In, ios::binary);
        ofstream outFile(filePath_Out, ios::binary);

        CryptoPP::FileSink file(filePath_Out.c_str());
        CryptoPP::ArraySource as(iv, CryptoPP::AES::BLOCKSIZE, true, new CryptoPP::Redirector(file));

        CryptoPP::FileSource{inFile, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::Redirector(file)}};
    }
    }
}

void CryptManager::decryptFile_AES_256(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode)
{
    CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH]; //КЛЮЧ

    if(sKey.length() < CryptoPP::AES::MAX_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::MAX_KEYLENGTH - sKey.size(), '*');
    }
    memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::FileSource fileSource(filePath_In.c_str(), false);

    CryptoPP::ArraySink as(iv, iv.size());
    fileSource.Attach(new CryptoPP::Redirector(as));
    fileSource.Pump(CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decipher(key, CryptoPP::AES::MAX_KEYLENGTH, iv);

        CryptoPP::ByteQueue queue;
        fileSource.Detach(new CryptoPP::StreamTransformationFilter(decipher, new CryptoPP::Redirector(queue)));
        fileSource.PumpAll();

        CryptoPP::FileSink fileSink(filePath_Out.c_str());
        queue.TransferTo(fileSink);
    }
    }
}

void CryptManager::decryptFile_AES_256_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath)
{
    CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH]; //КЛЮЧ

    if(sKey.length() < CryptoPP::AES::MAX_KEYLENGTH)
    {
        sKey += std::string(CryptoPP::AES::MAX_KEYLENGTH - sKey.size(), '*');
    }

    hashManager = new HashManager();
    string hashFile = hashManager->getHash_MD5(QString::fromLocal8Bit(keyFilePath.c_str())).toStdString();

    string newKey;
    for(int i = 0; i < CryptoPP::AES::MAX_KEYLENGTH; i++)
    {
        newKey = newKey + char((sKey[i] & hashFile[i]));
    }

    memcpy(key, newKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::FileSource fileSource(filePath_In.c_str(), false);

    CryptoPP::ArraySink as(iv, iv.size());
    fileSource.Attach(new CryptoPP::Redirector(as));
    fileSource.Pump(CryptoPP::AES::BLOCKSIZE);

    switch(mode)
    {
    case cryptMode::CFB:
    {
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decipher(key, CryptoPP::AES::MAX_KEYLENGTH, iv);

        CryptoPP::ByteQueue queue;
        fileSource.Detach(new CryptoPP::StreamTransformationFilter(decipher, new CryptoPP::Redirector(queue)));
        fileSource.PumpAll();

        CryptoPP::FileSink fileSink(filePath_Out.c_str());
        queue.TransferTo(fileSink);
    }
    }
}
