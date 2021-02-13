#include "signmanager.h"

//
#include <QDebug>
//


SignManager::SignManager()
{

}

void SignManager::GenKeyPair(string privKeyPath, string pubKeyPath)
{
    AutoSeededRandomPool rng;
    InvertibleRSAFunction privKey;
    privKey.Initialize(rng, 1024);

    Base64Encoder privKeySink(new FileSink(privKeyPath.c_str()));
    privKey.DEREncode(privKeySink);
    privKeySink.MessageEnd();

    RSAFunction pubKey(privKey);

    Base64Encoder pubKeySink(new FileSink(pubKeyPath.c_str()));
    pubKey.DEREncode(pubKeySink);
    pubKeySink.MessageEnd();
}

void SignManager::createSign(string filePath, string privKeyPath, string pubKeyPath, string signPath)
{
    string strContents;

    GenKeyPair(privKeyPath, pubKeyPath);

    FileSource(filePath.c_str(), true, new StringSink(strContents));

    AutoSeededRandomPool rng;

    //Чтение приватного ключа
    CryptoPP::ByteQueue bytes;
    FileSource file(privKeyPath.c_str(), true, new Base64Decoder);
    file.TransferTo(bytes);
    bytes.MessageEnd();
    RSA::PrivateKey privateKey;
    privateKey.Load(bytes);

    //Создание подписи
    RSASSA_PKCS1v15_SHA_Signer privkey(privateKey);
    SecByteBlock sbbSignature(privkey.SignatureLength());
    privkey.SignMessage(rng, (byte const*) strContents.data(), strContents.size(), sbbSignature);

    //Сохранение подписи
    FileSink sinksig(signPath.c_str());
    sinksig.Put(sbbSignature, sbbSignature.size());
}

bool SignManager::verifySign(string filePath, string signPath, string pubKeyPath)
{
    //Чтение публичного ключа
    CryptoPP::ByteQueue bytes;
    FileSource file(pubKeyPath.c_str(), true, new Base64Decoder);
    file.TransferTo(bytes);
    bytes.MessageEnd();
    RSA::PublicKey pubKey;
    pubKey.Load(bytes);

    RSASSA_PKCS1v15_SHA_Verifier verifier(pubKey);

    //Чтение файла
    string fileData;
    FileSource(filePath.c_str(), true, new StringSink(fileData));
    //Чтение подписи
    string signData;
    FileSource(signPath.c_str(), true, new StringSink(signData));

    string combined(fileData);
    combined.append(signData);

    //Проверка
    try
    {
        StringSource(combined, true, new SignatureVerificationFilter(verifier, NULL, SignatureVerificationFilter::THROW_EXCEPTION));
    }
    catch (SignatureVerificationFilter::SignatureVerificationFailed &err)
    {
        return false;
    }
    return true;
}


