#include "newpassrecord.h"
#include "ui_newpassrecord.h"

NewPassRecord::NewPassRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPassRecord)
{
    ui->setupUi(this);

    connect(ui->btnAdd, &QPushButton::clicked, this, &NewPassRecord::btnAdd_onClick);
}

NewPassRecord::~NewPassRecord()
{
    delete ui;
}

void NewPassRecord::btnAdd_onClick()
{
    RecordInfo recordInfo;
    recordInfo.name = ui->leName->text();
    recordInfo.login = ui->leLogin->text();
    recordInfo.URL = ui->leURL->text();
    recordInfo.password = ui->lePassword->text();
    recordInfo.description = ui->leDescr->text();

    emit accept(recordInfo);

    this->close();
}
