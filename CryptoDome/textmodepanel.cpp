#include "textmodepanel.h"
#include "ui_textmodepanel.h"

TextModePanel::TextModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextModePanel)
{
    ui->setupUi(this);
}

TextModePanel::~TextModePanel()
{
    delete ui;
}
