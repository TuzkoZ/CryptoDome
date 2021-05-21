#include "genpasswidget.h"
#include "ui_genpasswidget.h"

GenPassWidget::GenPassWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenPassWidget)
{
    ui->setupUi(this);
}

GenPassWidget::~GenPassWidget()
{
    delete ui;
}
