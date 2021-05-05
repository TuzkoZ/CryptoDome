#include "idlepanel.h"
#include "ui_idlepanel.h"

idlePanel::idlePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::idlePanel)
{
    ui->setupUi(this);
}

idlePanel::~idlePanel()
{
    delete ui;
}
