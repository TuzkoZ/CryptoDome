#include "passmngrsettings.h"
#include "ui_passmngrsettings.h"

PassMngrSettings::PassMngrSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassMngrSettings)
{
    ui->setupUi(this);

    connect(ui->btnBrowse, &QPushButton::clicked, this, &PassMngrSettings::btnBrowse_onClick);
    connect(ui->btnCreate, &QPushButton::clicked, this, &PassMngrSettings::btnCreate_onClick);
    connect(ui->btnAccept, &QPushButton::clicked, this, &PassMngrSettings::btnAccept_onClick);
}

PassMngrSettings::~PassMngrSettings()
{
    delete ui;
}

void PassMngrSettings::btnBrowse_onClick()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->lePassPath->setText(filePath);
    }
}

void PassMngrSettings::btnCreate_onClick()
{
    QString filePath = (QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Хранилище(*.crp)")));
    if(!filePath.isEmpty())
    {

        ui->lePassPath->setText(filePath);
    }

    bool ok;
    QString *masterKey = new QString(QInputDialog::getText(this, tr("Новый мастер-пароль"), tr("Введите новый мастер-пароль:"), QLineEdit::Normal, "", &ok));
    if(!masterKey->isEmpty())
    {
        ui->leMasterKey->setText(*masterKey);
    }

    StorageMngr *stMngr = new StorageMngr(ui->lePassPath->text(), ui->leMasterKey->text());
    stMngr->createStorage();

    delete stMngr;
    delete masterKey;
}

void PassMngrSettings::setStorageMngr(StorageMngr *storageMngr)
{
    this->storageMngr = storageMngr;
}

void PassMngrSettings::leMasterKeyChanged()
{
    storageMngr->setMasterKey(ui->leMasterKey->text());
}

void PassMngrSettings::btnAccept_onClick()
{
    StorageInfo stInfo;
    stInfo.storagePath = ui->lePassPath->text();
    stInfo.masterKey = ui->leMasterKey->text();
    emit accept(stInfo, crFlag);
}
