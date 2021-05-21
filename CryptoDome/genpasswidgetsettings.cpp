#include "genpasswidgetsettings.h"
#include "ui_genpasswidgetsettings.h"

GenPassWidgetSettings::GenPassWidgetSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenPassWidgetSettings)
{
    ui->setupUi(this);
}

GenPassWidgetSettings::~GenPassWidgetSettings()
{
    delete ui;
}
