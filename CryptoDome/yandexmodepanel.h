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
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
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
    QNetworkAccessManager *mngr;
    QFile *file;

private slots:
    void btnGetToken_onClick();
    void btnBrowseFile_onClick();
    void btnUploadFile_onClick();
    void getResponseUploadUrl(QNetworkReply *reply);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadFinished(QNetworkReply *reply);
};

#endif // YANDEXMODEPANEL_H
