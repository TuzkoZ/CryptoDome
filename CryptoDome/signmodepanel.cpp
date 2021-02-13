#include "signmodepanel.h"
#include "ui_signmodepanel.h"

#include <QDebug>

SignModePanel::SignModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignModePanel)
{
    ui->setupUi(this);

    connect(ui->rbGenNewKey, &QRadioButton::clicked, this, &SignModePanel::check_rbGenKey);
    connect(ui->rbUseKey, &QRadioButton::clicked, this, &SignModePanel::check_rbGenKey);
    connect(ui->btnCreateSign, &QPushButton::clicked, this, &SignModePanel::onClick_btnCreateSign);
    connect(ui->btnVerifySign, &QPushButton::clicked, this, &SignModePanel::onClick_btnVerifySign);
    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowseFilePath);
    connect(ui->btnBrowseSign, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowseSignPath);
    connect(ui->btnBrowsePubKeyPath, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowsePubKeyPath);
    connect(ui->btnBrowsePrKeyPath, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowsePrKeyPath);
    connect(ui->btnBrowseKey, &QPushButton::clicked, this, &SignModePanel::onCLick_btnBrowseKeyPath);
    connect(ui->btnBrowseFileV, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowseFilePathV);
    connect(ui->btnBrowseSignV, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowseSignPathV);
    connect(ui->btnBrowseKeyV, &QPushButton::clicked, this, &SignModePanel::onClick_btnBrowsePubKeyPathV);
    connect(ui->btnVerifySign, &QPushButton::clicked, this, &SignModePanel::onClick_btnVerifySign);

}

SignModePanel::~SignModePanel()
{
    delete ui;
}

void SignModePanel::check_rbGenKey()
{
    if(ui->rbGenNewKey->isChecked())
    {
        ui->leKeyPath->setEnabled(false);
        ui->btnBrowseKey->setEnabled(false);
        ui->lePrKeyPath->setEnabled(true);
        ui->btnBrowsePrKeyPath->setEnabled(true);
    }
    if(ui->rbUseKey->isChecked())
    {
        ui->leKeyPath->setEnabled(true);
        ui->btnBrowseKey->setEnabled(true);
        ui->lePrKeyPath->setEnabled(false);
        ui->btnBrowsePrKeyPath->setEnabled(false);
    }
}

void SignModePanel::onClick_btnCreateSign()
{
    if(ui->rbGenNewKey->isChecked())
    {
        if(ui->leFilePath->text().isEmpty() || ui->leSignPath->text().isEmpty() || ui->lePubKeyPath->text().isEmpty() || ui->lePrKeyPath->text().isEmpty())
        {
            showMessage("Ошибка", "Необходимо указать все пути");
        }
        else
        {
            SignManager *signManager = new SignManager();
            signManager->createSign(ui->leFilePath->text().toStdString(), ui->lePrKeyPath->text().toStdString(), ui->lePubKeyPath->text().toStdString(), ui->leSignPath->text().toStdString());
            showMessage("Создание подписи", "Создание подписи успешно выполнено");
        }
    }
    else
    {
        if(ui->leFilePath->text().isEmpty() || ui->leSignPath->text().isEmpty() || ui->lePubKeyPath->text().isEmpty() || ui->leKeyPath->text().isEmpty())
        {
            showMessage("Ошибка", "Необходимо указать все пути");
        }
        else
        {
            SignManager *signManager = new SignManager();
            signManager->createSign(ui->leFilePath->text().toStdString(), ui->leKeyPath->text().toStdString(), ui->lePubKeyPath->text().toStdString(), ui->leSignPath->text().toStdString());
            showMessage("Создание подписи", "Создание подписи успешно выполнено");
        }
    }
}

void SignModePanel::onClick_btnVerifySign()
{
    if(ui->leFilePathV->text().isEmpty() || ui->leKeyPathV->text().isEmpty() || ui->leSignPathV->text().isEmpty())
    {
        showMessage("Ошибка", "Необходимо указать все пути");
    }
    else
    {
        SignManager *signManager = new SignManager();
        if(signManager->verifySign(ui->leFilePathV->text().toStdString(), ui->leSignPathV->text().toStdString(), ui->leKeyPathV->text().toStdString()))
        {
            ui->leVerifyResult->setText("Подпись успешно прошла проверку");
        }
        else
        {
            ui->leVerifyResult->setText("Неверная подпись");
        }
    }
}

void SignModePanel::showMessage(QString title, QString text)
{
    QMessageBox msg;
    msg.setWindowTitle(title);
    msg.setText(text);
    msg.exec();
}

void SignModePanel::onClick_btnBrowseFilePath()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leFilePath->setText(filePath);
        ui->lePubKeyPath->setText(filePath + ".pubkey");
        ui->leSignPath->setText(filePath + ".sign");
        if(ui->rbGenNewKey->isChecked())
        {
            ui->lePrKeyPath->setText(filePath + ".key");
        }
    }
}

void SignModePanel::onCLick_btnBrowseKeyPath()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leKeyPath->setText(filePath);
    }
}

void SignModePanel::onClick_btnBrowseSignPath()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Подпись (*.sign)"));
    ui->leSignPath->setText(filePath);
}

void SignModePanel::onClick_btnBrowsePubKeyPath()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Публичный ключ (*.pubkey)"));
    ui->lePubKeyPath->setText(filePath);
}

void SignModePanel::onClick_btnBrowsePrKeyPath()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Приватный ключ (*.key)"));
    ui->lePrKeyPath->setText(filePath);
}

void SignModePanel::onClick_btnBrowseFilePathV()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leFilePathV->setText(filePath);
    }
}

void SignModePanel::onClick_btnBrowseSignPathV()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл подписи"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leSignPathV->setText(filePath);
    }
}

void SignModePanel::onClick_btnBrowsePubKeyPathV()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл публичного ключа"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leKeyPathV->setText(filePath);
    }
}
