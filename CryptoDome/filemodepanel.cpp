#include "filemodepanel.h"
#include "ui_filemodepanel.h"

FileModePanel::FileModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileModePanel)
{
    ui->setupUi(this);
}

FileModePanel::~FileModePanel()
{
    delete ui;
}
