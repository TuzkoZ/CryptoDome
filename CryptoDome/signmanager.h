#ifndef SIGNMANAGER_H
#define SIGNMANAGER_H

#include <string>
#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <files.h>

using namespace CryptoPP;
using namespace std;

class SignManager
{
public:
    SignManager();
    void createSign(string filePath, string privKeyPath, string pubKeyPath, string signPath);
    bool verifySign(string filePath, string signPath, string pubKeyPath);

private:
    void GenKeyPair(string privKeyPath, string pubKeyPath);
};

#endif // SIGNMANAGER_H
