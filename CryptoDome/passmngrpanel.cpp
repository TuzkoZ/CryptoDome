#include "passmngrpanel.h"
#include "ui_passmngrpanel.h"

PassMngrPanel::PassMngrPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassMngrPanel)
{
    ui->setupUi(this);

//    storageMngr = new StorageMngr();

    passMngrSettings = new PassMngrSettings(this);
//    passMngrSettings->setStorageMngr(storageMngr);
//    ui->stackedWidget->addWidget(passMngrSettings);

//    passMngrStorage = new PassMngrStorage(this);
//    passMngrStorage->setStorageMngr(storageMngr);
//    ui->stackedWidget->addWidget(passMngrStorage);

    layout = new QVBoxLayout();
    layout->addWidget(passMngrSettings);
    ui->widget->setLayout(layout);

//    ui->btnBack->setEnabled(false);

//    connect(ui->btnNext, &QPushButton::clicked, this, &PassMngrPanel::btnNext_onClick);
//    connect(ui->btnBack, &QPushButton::clicked, this, &PassMngrPanel::btnBack_onClick);
    connect(passMngrSettings, &PassMngrSettings::accept, this, &PassMngrPanel::openStorage);
}

PassMngrPanel::~PassMngrPanel()
{
    delete ui;
}

//void PassMngrPanel::btnNext_onClick()
//{
//    if(ui->stackedWidget->currentWidget() == passMngrSettings)
//    {
//        ui->btnBack->setEnabled(true);
//        ui->btnNext->setEnabled(false);
//        ui->stackedWidget->setCurrentWidget(passMngrStorage);
//        storageMngr->readToStorage();
//    }
//}

//void PassMngrPanel::btnBack_onClick()
//{
//    if(ui->stackedWidget->currentWidget() == passMngrStorage)
//    {
//        ui->btnBack->setEnabled(false);
//        ui->btnNext->setEnabled(true);
//        ui->stackedWidget->setCurrentWidget(passMngrSettings);
//    }
//}

void PassMngrPanel::openStorage(StorageInfo stInfo)
{
    PassMngrStorage *passMngrStorageWin = new PassMngrStorage();
    passMngrStorageWin->setStorageInfo(stInfo);

    clearLayout(ui->widget->layout());
    layout->addWidget(passMngrStorageWin);
}

void PassMngrPanel::clearLayout(QLayout *layout)
{
    if (layout) {
        while(layout->count() > 0){
            QLayoutItem *item = layout->takeAt(0);
            QWidget* widget = item->widget();
            if(widget)
                delete widget;
            delete item;
        }
    }
}
