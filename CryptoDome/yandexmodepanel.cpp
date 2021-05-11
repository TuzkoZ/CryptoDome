#include "yandexmodepanel.h"
#include "ui_yandexmodepanel.h"

YandexModePanel::YandexModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YandexModePanel)
{
    ui->setupUi(this);

    ui->leNewFileName->setPlaceholderText("Введите новое имя файла без расширения");
    ui->lePassword->setPlaceholderText("Максимальная длина: 32 символов");

    connect(ui->btnGetToken, &QPushButton::clicked, this, &YandexModePanel::btnGetToken_onClick);
    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &YandexModePanel::btnBrowseFile_onClick);
    connect(ui->btnUploadFile, &QPushButton::clicked, this, &YandexModePanel::btnUploadFile_onClick);
}

YandexModePanel::~YandexModePanel()
{
    delete ui;
}

void YandexModePanel::btnGetToken_onClick()
{
    QUrl url = QUrl("https://oauth.yandex.ru/authorize?response_type=token&client_id=92e93a754a6046fdaec12f0c11d69b85");
    QDesktopServices::openUrl(url);
}

void YandexModePanel::btnBrowseFile_onClick()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leFilePath->setText(filePath);
    }
}

void YandexModePanel::btnUploadFile_onClick()
{
    if(ui->leToken->text().isEmpty())
    {
        qDebug() << "Необходимо ввести токен";
    }
    else
    {
        if(ui->leFilePath->text().isEmpty())
        {
            qDebug() << "Необходимо выбрать файл";
        }
        else
        {
            if(ui->lePassword->text().isEmpty())
            {
                qDebug() << "Пароль не должен быть пустым";
            }
            else
            {
                mngr = new QNetworkAccessManager();
                string filePath = ui->leFilePath->text().toStdString();
                string fileName = QFileInfo(ui->leFilePath->text()).completeBaseName().toStdString();
                string newFileName = fileName + ".crd";
                tmpNewFilePath = QCoreApplication::applicationDirPath().toStdString() + "\\" + newFileName;

                crypter->encryptFile_AES_256(filePath, tmpNewFilePath, ui->lePassword->text().toStdString(), cryptMode::CFB);

                QNetworkRequest request(QUrl(("https://cloud-api.yandex.net/v1/disk/resources/upload?path=" + QString::fromLocal8Bit(newFileName.c_str()))));
                request.setRawHeader("Authorization", ui->leToken->text().toLocal8Bit());
                connect(mngr, SIGNAL(finished(QNetworkReply*)), SLOT(getResponseUploadUrl(QNetworkReply*)));
                connect(mngr, &QNetworkAccessManager::finished, this, &YandexModePanel::uploadFinished);
                mngr->get(request);
                ui->btnUploadFile->setEnabled(false);
            }
        }
    }
}

void YandexModePanel::getResponseUploadUrl(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = document.object();
    QString url = obj["href"].toString();

    file = new QFile(QString::fromLocal8Bit(tmpNewFilePath.c_str()));

    if(file->open(QIODevice::ReadOnly))
    {
        QNetworkReply *reply = mngr->put(QNetworkRequest(url), file);
        connect(reply, &QNetworkReply::uploadProgress, this, &YandexModePanel::uploadProgress);
    }
}

void YandexModePanel::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    QString text = "Загрузка на сервер: Всего байт [" + QString::number(bytesTotal) + "] / Загружено [" + QString::number(bytesSent) + "]";
    ui->leProgress->setText(text);

    if(bytesSent == bytesTotal)
    {
        ui->btnUploadFile->setEnabled(true);
        ui->leProgress->clear();
        file->close();
        QFile::remove(QString::fromLocal8Bit(tmpNewFilePath.c_str()));
    }
}

void YandexModePanel::uploadFinished(QNetworkReply *reply)
{
    reply->deleteLater();
}
