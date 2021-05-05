#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

#include <files.h>
#include <modes.h>
#include <osrng.h>
#include <QString>
#include <QDebug>
#include <cstddef>
#include "hashmanager.h"

enum cryptMode{CFB};

using namespace std;

using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

class CryptManager
{
public:
    CryptManager();
    void encryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
    void encryptFile_AES_128_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath); //Использование файла вместе с ключом
    void decryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
    void decryptFile_AES_128_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath);
    void encryptFile_AES_256(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
    void encryptFile_AES_256_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath);
    void decryptFile_AES_256(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
    void decryptFile_AES_256_KF(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode, const string &keyFilePath);

private:
    HashManager *hashManager;
};

#endif // CRYPTMANAGER_H
