#include "filemodepanel.h"
#include "ui_filemodepanel.h"

FileModePanel::FileModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileModePanel)
{
    ui->setupUi(this);

    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &FileModePanel::onClick_btnBrowseFile);
    connect(ui->btnBrowseFile_D, &QPushButton::clicked, this, &FileModePanel::onClick_btnBrowseFile_D);
    connect(ui->btnEncryptFile, &QPushButton::clicked, this, &FileModePanel::onClick_btnEncryptFile);
    connect(ui->btnEncryptFile_D, &QPushButton::clicked, this, &FileModePanel::onClick_btnDecryptFile);
}

FileModePanel::~FileModePanel()
{
    delete ui;
}

void FileModePanel::onClick_btnBrowseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(filePath.isEmpty() == false)
    {
        ui->leFilePath->setText(filePath);
    }
}

void FileModePanel::onClick_btnEncryptFile()
{
    if(ui->leFilePath->text().isEmpty() == true)
    {
        showMsg("Ошибка", "Путь к файлу не должен быть пустым");
    }
    else
    {
        if(checkFile(ui->leFilePath->text()) != true)
        {
            showMsg("Ошибка", "Файл не найден или не может быть открыт");
        }
        else
        {
            if(ui->leKey->text().isEmpty() == true)
            {
                showMsg("Ошибка заполнения", "Ключ не должен оставаться пустым");
            }
            else
            {
                string key = ui->leKey->text().toStdString();
                string filePath = ui->leFilePath->text().toStdString();
                QString filePathOut = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Все файлы (*)"));
                if(filePathOut.isEmpty() == false)
                {
                    string filePathOut_s = filePathOut.toStdString();
                    CryptManager *cryptManager = new CryptManager();
                    cryptManager->encryptFile_AES_128(filePath, filePathOut_s, key, cryptMode::CFB);
                }
            }
        }
    }
}

void FileModePanel::onClick_btnDecryptFile()
{
    if(ui->leFilePath_D->text().isEmpty() == true)
    {
        showMsg("Ошибка", "Путь к файлу не должен быть пустым");
    }
    else
    {
        if(checkFile(ui->leFilePath_D->text()) != true)
        {
            showMsg("Ошибка", "Файл не найден или не может быть открыт");
        }
        else
        {
            if(ui->leKey_D->text().isEmpty() == true)
            {
                showMsg("Ошибка заполнения", "Ключ не должен оставаться пустым");
            }
            else
            {
                string key = ui->leKey_D->text().toStdString();
                string filePath = ui->leFilePath_D->text().toStdString();
                QString filePathOut = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Все файлы (*)"));
                if(filePathOut.isEmpty() == false)
                {
                    string filePathOut_s = filePathOut.toStdString();
                    CryptManager *cryptManager = new CryptManager();
                    cryptManager->decryptFile_AES_128(filePath, filePathOut_s, key, cryptMode::CFB);
                }
            }
        }
    }
}

void FileModePanel::showMsg(QString title, QString text)
{
    QMessageBox msg;
    msg.setWindowTitle(title);
    msg.setText(text);
    msg.exec();
}

bool FileModePanel::checkFile(QString file)
{
    QFileInfo fileInfo(file);
    if(fileInfo.exists() && fileInfo.isFile())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FileModePanel::onClick_btnBrowseFile_D()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(filePath.isEmpty() == false)
    {
        ui->leFilePath_D->setText(filePath);
    }
}
