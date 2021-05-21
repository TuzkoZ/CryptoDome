#include "passmngrstorage.h"
#include "ui_passmngrstorage.h"

PassMngrStorage::PassMngrStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassMngrStorage)
{
    ui->setupUi(this);



    connect(ui->btnUpdate, &QPushButton::clicked, this, &PassMngrStorage::updateStorageSlot);
    connect(ui->btnPassAdd, &QPushButton::clicked, this, &PassMngrStorage::btnAdd_onClick);
    connect(ui->tableView, &QTableView::clicked, this, &PassMngrStorage::cellClicked);
    connect(ui->btnPassSave, &QPushButton::clicked, this, &PassMngrStorage::btnSave_onClick);
    connect(ui->btnPassDel, &QPushButton::clicked, this, &PassMngrStorage::btnDel_onClick);
}

PassMngrStorage::~PassMngrStorage()
{
    delete ui;
}

void PassMngrStorage::setStorageMngr(StorageMngr storageMngr)
{
    this->storageMngr = &storageMngr;
}

void PassMngrStorage::updateStorageSlot()
{ 
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *item;

    if(storageMngr->storage.size() != 0)
    {
        int count = 0;
        foreach(PassRecord record, storageMngr->storage)
        {
            item = new QStandardItem(record.getName());
            model->setItem(count, 0, item);
            count = count + 1;
        }

        updateTable(model);
    }

    qDebug() << "t1" << storageMngr->storage.size();
}

void PassMngrStorage::btnAdd_onClick()
{
    NewPassRecord *newPassRecord = new NewPassRecord();
    newPassRecord->setWindowTitle("Добавить новый пароль");
    newPassRecord->show();

    connect(newPassRecord, &NewPassRecord::accept, this, &PassMngrStorage::addRecord);
}

void PassMngrStorage::btnPassSave_onClick()
{
    PassRecord record(ui->lePassName->text(), ui->lePassURL->text(), ui->lePassLogin->text(), ui->lePassPassword->text(), ui->lePassDescr->text());
    storageMngr->storage.push_back(record);
}


void PassMngrStorage::updateTable(QStandardItemModel *model)
{
    QStringList horizontalHeader;
    horizontalHeader.append("Имя");

    model->setHorizontalHeaderLabels(horizontalHeader);

    ui->tableView->setModel(model);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void PassMngrStorage::createStorage()
{
    storageMngr->createStorage();
}

void PassMngrStorage::setStorageInfo(StorageInfo stInfo)
{
    this->storageMngr = new StorageMngr(stInfo.storagePath, stInfo.masterKey);
}

void PassMngrStorage::cellClicked()
{
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();

    foreach(PassRecord record, storageMngr->storage)
    {
        if(record.getName() == name)
        {
            ui->lePassName->setText(record.getName());
            ui->lePassURL->setText(record.getURL());
            ui->lePassLogin->setText(record.getLogin());
            ui->lePassPassword->setText(record.getPassword());
            ui->lePassDescr->setText(record.getDescription());

            ui->lePassDescr->setEnabled(true);
            ui->lePassLogin->setEnabled(true);
            ui->lePassPassword->setEnabled(true);
            ui->lePassURL->setEnabled(true);
            ui->lePassName->setEnabled(true);
            ui->btnPassSave->setEnabled(true);
        }
    }
}

void PassMngrStorage::btnSave_onClick()
{
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
    if(name == ui->lePassName->text())
    {
        storageMngr->saveRecordInfo(ui->lePassName->text(), ui->lePassURL->text(), ui->lePassLogin->text(), ui->lePassPassword->text(), ui->lePassDescr->text());
    }
    updateStorageSlot();
}

void PassMngrStorage::addRecord(RecordInfo recInfo)
{
    storageMngr->addRecord(recInfo.name, recInfo.URL, recInfo.login, recInfo.password, recInfo.description);
    updateStorageSlot();
}

void PassMngrStorage::btnDel_onClick()
{
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
    storageMngr->delRecord(name);
    updateStorageSlot();
}
