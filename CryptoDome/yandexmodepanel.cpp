#include "yandexmodepanel.h"
#include "ui_yandexmodepanel.h"

YandexModePanel::YandexModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YandexModePanel)
{
    ui->setupUi(this);
    ui->lePassword->setPlaceholderText("Максимальная длина: 32 символов");

    mngr = new QNetworkAccessManager();

    connect(ui->btnGetToken, &QPushButton::clicked, this, &YandexModePanel::btnGetToken_onClick);
    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &YandexModePanel::btnBrowseFile_onClick);
    connect(ui->btnUploadFile, &QPushButton::clicked, this, &YandexModePanel::btnUploadFile_onClick);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &YandexModePanel::btnUpdate_onClick);
    connect(ui->btnDownload, &QPushButton::clicked, this, &YandexModePanel::btnDownload_onClick);
    connect(ui->btnDelete, &QPushButton::clicked, this, &YandexModePanel::btnDeleteFile_onClick);
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
        ui->leProgress->setText("Файл успешно загружен на Яндекс Диск");
        ui->btnUploadFile->setEnabled(true);
        file->close();
        QFile::remove(QString::fromLocal8Bit(tmpNewFilePath.c_str()));
        btnUpdate_onClick();
    }
}

void YandexModePanel::uploadFinished(QNetworkReply *reply)
{
    reply->deleteLater();
}

void YandexModePanel::btnUpdate_onClick()
{
    if(ui->leToken->text().isEmpty())
    {
        qDebug() << "Необходимо ввести токен";
    }
    else
    {
        QNetworkAccessManager *mngrUpdate = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("https://cloud-api.yandex.net/v1/disk/resources/files"));
        request.setRawHeader("Authorization", ui->leToken->text().toLocal8Bit());
        connect(mngrUpdate, SIGNAL(finished(QNetworkReply*)), SLOT(getResonseUpdateFileList(QNetworkReply*)));
        mngrUpdate->get(request);
    }
}

void YandexModePanel::getResonseUpdateFileList(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = document.object();
    QJsonArray array = obj["items"].toArray();

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *item;

    int count = 0;

    foreach(QJsonValue jval, array)
    {
        QJsonObject obj = jval.toObject();

        if(obj.value("name").toString().right(3) == "crd")
        {
            qDebug() << "Name: " << obj.value("name").toString() << " || Path: " << obj.value("path").toString();

            item = new QStandardItem(obj.value("name").toString());
            model->setItem(count, 0, item);
            item = new QStandardItem(obj.value("path").toString());
            model->setItem(count, 1, item);
            count = count + 1;
        }
    }

    updateTable(model);
}

void YandexModePanel::updateTable(QStandardItemModel *model)
{
    QStringList horizontalHeader;
    horizontalHeader.append("Имя файла");
    horizontalHeader.append("Путь к файлу");

    model->setHorizontalHeaderLabels(horizontalHeader);

    ui->tvFileList->setModel(model);

    ui->tvFileList->resizeRowsToContents();
    ui->tvFileList->resizeColumnsToContents();

}

void YandexModePanel::btnDownload_onClick()
{  
    QString path = ui->tvFileList->model()->data(ui->tvFileList->model()->index(ui->tvFileList->currentIndex().row(), 1)).toString();

    if(path == "")
    {

    }
    else
    {
        downloadFilePath = (QFileDialog::QFileDialog::getSaveFileName( 0,"Сохранить файл как","","") + "_");

        if(!downloadFilePath.isEmpty())
        {
            mngrDownload = new QNetworkAccessManager();
            QNetworkRequest request(QUrl(("https://cloud-api.yandex.net/v1/disk/resources/download?path=" + path)));
            request.setRawHeader("Authorization", ui->leToken->text().toLocal8Bit());
            connect(mngrDownload, SIGNAL(finished(QNetworkReply*)), SLOT(getResponseDownloadUrl(QNetworkReply*)));
            //connect(mngrDownload, &QNetworkAccessManager::finished, this, &YandexModePanel::uploadFinished);
            mngrDownload->get(request);
            ui->btnDownload->setEnabled(false);
        }
    }

}

void YandexModePanel::getResponseDownloadUrl(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = document.object();
    QString url = obj["href"].toString();

    qDebug() << url;

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Safari/537.36 OPR/73.0.3856.438");
    request.setRawHeader("Authorization", ui->leToken->text().toLocal8Bit());
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
    mngrDownloadFile = new QNetworkAccessManager();
    connect(mngrDownloadFile, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponseFile()));

    downloadReply = mngrDownloadFile->get(request);

    downloadArray.clear();

    connect(downloadReply, &QNetworkReply::readyRead, this, &YandexModePanel::getResponseFile);
    connect(downloadReply, &QNetworkReply::downloadProgress, this, &YandexModePanel::downloadProgress);
}

void YandexModePanel::getResponseFile()
{
    downloadArray.append(downloadReply->readAll());
    downloadFile = new QFile(downloadFilePath);
    if(downloadReply->isFinished())
    {
        writeFile(downloadArray);
    }
}

void YandexModePanel::writeFile(QByteArray array)
{
    QFile *downloadFile_ = new QFile(downloadFilePath);
    if(downloadFile_->open(QIODevice::WriteOnly))
    {
        downloadFile_->write(array);
    }
    downloadFile_->flush();
    downloadFile_->close();

    encryptFile();
}

void YandexModePanel::downloadProgress(qint64 bytesGet, qint64 bytesTotal)
{
    QString text = "Скачивание файла: Всего байт [" + QString::number(bytesTotal) + "] / Загружено [" + QString::number(bytesGet) + "]";
    qDebug() << text;
    ui->leProgress->setText(text);

    if(bytesGet == bytesTotal)
    {
        ui->leProgress->setText("Файл успешно загружен");
        ui->btnDownload->setEnabled(true);
    }
}

void YandexModePanel::encryptFile()
{
    bool ok;
    QString password = QInputDialog::getText(this, tr("Введите пароль"), tr("Пароль:\nОставьте поле пустым, чтобы просто скачать файл"), QLineEdit::Normal, "", &ok);
    if(ok && !password.isEmpty())
    {
          CryptManager *crypter = new CryptManager();

          crypter->decryptFile_AES_256(downloadFilePath.toStdString(), downloadFilePath.toStdString().substr(0, downloadFilePath.length() - 1) , password.toStdString(), cryptMode::CFB);
          qDebug() << downloadFilePath.chopped(1);
          QFile::remove(downloadFilePath);
          crFlag = false;
    }
    if(ok && password.isEmpty())
    {
        crFlag = false;
    }
}

void YandexModePanel::btnDeleteFile_onClick()
{
    QString path = ui->tvFileList->model()->data(ui->tvFileList->model()->index(ui->tvFileList->currentIndex().row(), 1)).toString();

    if(path == "")
    {

    }
    else
    {
        mngrDelete = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("https://cloud-api.yandex.net/v1/disk/resources?path=" + path + "&permanently=true"));
        request.setRawHeader("Authorization", ui->leToken->text().toLocal8Bit());
        connect(mngrDelete, &QNetworkAccessManager::finished, this, &YandexModePanel::getResponseDeleteFile);
        mngrDelete->deleteResource(request);
    }
}

void YandexModePanel::getResponseDeleteFile(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
    btnUpdate_onClick();
}
