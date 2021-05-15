#ifndef YANDEXMODEPANEL_H
#define YANDEXMODEPANEL_H

#include <QWidget>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QInputDialog>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QStandardItemModel>
#include "cryptmanager.h"

namespace Ui {
class YandexModePanel;
}

class YandexModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit YandexModePanel(QWidget *parent = nullptr);
    ~YandexModePanel();

private:
    Ui::YandexModePanel *ui;
    CryptManager *crypter;
    string tmpNewFilePath;
    QString downloadFilePath;
    QNetworkAccessManager *mngr;
    QNetworkAccessManager *mngrDownload;
    QNetworkAccessManager *mngrDownloadFile;
    QNetworkAccessManager *mngrDelete;
    QFile *file;
    QFile *downloadFile;
    QNetworkReply *downloadReply;
    QByteArray downloadArray;
    bool crFlag = false;

    void updateTable(QStandardItemModel *model);
    void writeFile(QByteArray array);
    void encryptFile();

private slots:
    void btnGetToken_onClick();
    void btnBrowseFile_onClick();
    void btnUploadFile_onClick();
    void btnDeleteFile_onClick();
    void getResponseDeleteFile(QNetworkReply *reply);
    void getResponseUploadUrl(QNetworkReply *reply);
    void getResonseUpdateFileList(QNetworkReply *reply);
    void getResponseFile();
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadFinished(QNetworkReply *reply);
    void getResponseDownloadUrl(QNetworkReply *reply);
    void btnUpdate_onClick();
    void btnDownload_onClick();
    void downloadProgress(qint64 bytesGet, qint64 bytesTotal);
};

#endif // YANDEXMODEPANEL_H
