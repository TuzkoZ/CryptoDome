#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

#include <files.h>
#include <modes.h>
#include <osrng.h>
#include <QString>
#include <cstddef>

enum cryptMode{CFB};

using namespace std;

using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

class CryptManager
{
public:
    CryptManager();
    void encryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
    void decryptFile_AES_128(const string &filePath_In, const string &filePath_Out, string sKey, cryptMode mode);
};

#endif // CRYPTMANAGER_H
