#include "filemodepanel.h"
#include "ui_filemodepanel.h"

FileModePanel::FileModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileModePanel)
{
    ui->setupUi(this);

    ui->leKey->setPlaceholderText("Максимальная длина: 16 символов");
    ui->leKey_D->setPlaceholderText("Максимальная длина: 16 символов");

    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &FileModePanel::onClick_btnBrowseFile);
    connect(ui->btnBrowseFile_D, &QPushButton::clicked, this, &FileModePanel::onClick_btnBrowseFile_D);
    connect(ui->btnEncryptFile, &QPushButton::clicked, this, &FileModePanel::onClick_btnEncryptFile);
    connect(ui->btnEncryptFile_D, &QPushButton::clicked, this, &FileModePanel::onClick_btnDecryptFile);
    connect(ui->cbAlgorithm, SIGNAL(activated(int)), this, SLOT(comboBox_select(int)));
    connect(ui->cbAlgorithm_D, SIGNAL(activated(int)), this, SLOT(comboBox_select(int)));
    connect(ui->cbKeyFile, SIGNAL(clicked()), this, SLOT(cbKeyFile_clicked()));
    connect(ui->btnBrowseKeyFile, SIGNAL(clicked()), this, SLOT(btnBrowseKeyFile_onClick()));
    connect(ui->cbKeyFile_D, SIGNAL(clicked()), this, SLOT(cbKeyFile_clicked()));
    connect(ui->btnBrowseKeyFile_D, SIGNAL(clicked()), this, SLOT(btnBrowseKeyFile_D_onClick()));

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
                    cryptMode currentCryptMode;

                    switch(ui->cbMode->currentIndex())
                    {
                    case 0:
                    {
                        currentCryptMode = cryptMode::CFB;
                        break;
                    }
                    }

                    switch(ui->cbAlgorithm->currentIndex())
                    {
                    case 0:
                    {
                        if(ui->cbKeyFile->isChecked())
                        {
                            cryptManager->encryptFile_AES_128_KF(filePath, filePathOut_s, key, cryptMode::CFB, ui->leKeyFilePath->text().toStdString());
                            break;
                        }
                        else
                        {
                            cryptManager->encryptFile_AES_128(filePath, filePathOut_s, key, cryptMode::CFB);
                            break;
                        }
                    }
                    case 1:
                    {
                        if(ui->cbKeyFile->isChecked())
                        {
                            qDebug() << "!";
                            cryptManager->encryptFile_AES_256_KF(filePath, filePathOut_s, key, cryptMode::CFB, ui->leKeyFilePath->text().toStdString());
                            break;
                        }
                        else
                        {
                            cryptManager->encryptFile_AES_256(filePath, filePathOut_s, key, cryptMode::CFB);
                            break;
                        }
                    }
                    }

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

                    cryptMode currentCryptMode;

                    switch(ui->cbMode_D->currentIndex())
                    {
                    case 0:
                    {
                        currentCryptMode = cryptMode::CFB;
                        break;
                    }
                    }

                    switch(ui->cbAlgorithm_D->currentIndex())
                    {
                    case 0:
                    {
                        if(ui->cbKeyFile_D->isChecked())
                        {
                            cryptManager->decryptFile_AES_128_KF(filePath, filePathOut_s, key, cryptMode::CFB, ui->leKeyFilePath_D->text().toStdString());
                            break;
                        }
                        else
                        {
                            cryptManager->decryptFile_AES_128(filePath, filePathOut_s, key, cryptMode::CFB);
                            break;
                        }
                    }
                    case 1:
                    {
                        if(ui->cbKeyFile_D->isChecked())
                        {
                            qDebug() << "!";
                            cryptManager->decryptFile_AES_256_KF(filePath, filePathOut_s, key, cryptMode::CFB, ui->leKeyFilePath_D->text().toStdString());
                            break;
                        }
                        else
                        {
                            cryptManager->decryptFile_AES_256(filePath, filePathOut_s, key, cryptMode::CFB);
                            break;
                        }
                    }
                    }
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

void FileModePanel::comboBox_select(int i)
{
    if(ui->cbAlgorithm->currentIndex() == 0)
    {
        ui->leKey->clear();
        ui->leKey->setPlaceholderText("Максимальная длина: 16 символов");
        ui->leKey->setMaxLength(16);
    }
    else if(ui->cbAlgorithm->currentIndex() == 1)
    {
        ui->leKey->clear();
        ui->leKey->setPlaceholderText("Максимальная длина: 32 символа");
        ui->leKey->setMaxLength(32);
    }

    if(ui->cbAlgorithm_D->currentIndex() == 0)
    {
        ui->leKey_D->clear();
        ui->leKey_D->setPlaceholderText("Максимальная длина: 16 символов");
        ui->leKey_D->setMaxLength(16);
    }
    else if(ui->cbAlgorithm_D->currentIndex() == 1)
    {
        ui->leKey_D->clear();
        ui->leKey_D->setPlaceholderText("Максимальная длина: 32 символа");
        ui->leKey_D->setMaxLength(32);
    }
}

void FileModePanel::cbKeyFile_clicked()
{
    if(ui->cbKeyFile->isChecked())
    {
        ui->leKeyFilePath->setEnabled(true);
        ui->btnBrowseKeyFile->setEnabled(true);
    }
    else
    {
        ui->leKeyFilePath->setEnabled(false);
        ui->btnBrowseKeyFile->setEnabled(false);
    }

    if(ui->cbKeyFile_D->isChecked())
    {
        ui->leKeyFilePath_D->setEnabled(true);
        ui->btnBrowseKeyFile_D->setEnabled(true);
    }
    else
    {
        ui->leKeyFilePath_D->setEnabled(false);
        ui->btnBrowseKeyFile_D->setEnabled(false);
    }
}

void FileModePanel::btnBrowseKeyFile_onClick()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(filePath.isEmpty() == false)
    {
        ui->leKeyFilePath->setText(filePath);
    }
}

void FileModePanel::btnBrowseKeyFile_D_onClick()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(filePath.isEmpty() == false)
    {
        ui->leKeyFilePath_D->setText(filePath);
    }
}
