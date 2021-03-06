#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/new/prefix1/Resources/safeIcon.png"));

    ui->btnTextModePanel->setVisible(false);

    idleModePanel = new idlePanel();
    ui->verticalLayout_4->insertWidget(0, idleModePanel);

    connect(ui->btnFileModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnFileModePanel);
    connect(ui->btnTextModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnTextModePanel);
    connect(ui->btnSignModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnSignModePanel);
    connect(ui->btnHashModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnHashModePanel);
    connect(ui->btnYandexModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnYandexModePanel);
    connect(ui->actionGenPassword, &QAction::triggered, this, &MainWindow::showGeneratePasswordDialog);
    connect(ui->btnPassMngr, &QPushButton::clicked, this, &MainWindow::onClick_btnPassMngrPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClick_btnFileModePanel()
{
    if(fileModeIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            fileModeIsOpened = false;
        }
        clearLayout();
        fileModePanel = new FileModePanel();
        ui->verticalLayout_4->insertWidget(0, fileModePanel);
        fileModeIsOpened = true;
        textModeIsOpened = false;
        hashModeIsOpened = false;
        signModeIsOpened = false;
        passMngrIsOpened = false;
        yandexModeIsOpened = false;

    }
}

void MainWindow::onClick_btnTextModePanel()
{
    if(textModeIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            fileModeIsOpened = false;
        }
        clearLayout();
        textModePanel = new TextModePanel();
        ui->verticalLayout_4->insertWidget(1, textModePanel);
        textModeIsOpened = true;
        fileModeIsOpened = false;
        hashModeIsOpened = false;
        signModeIsOpened =false;
        passMngrIsOpened = false;
        yandexModeIsOpened = false;
    }
}

void MainWindow::onClick_btnSignModePanel()
{
    if(signModeIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            signModeIsOpened = false;
        }
        clearLayout();
        signModePanel = new SignModePanel();
        ui->verticalLayout_4->insertWidget(1, signModePanel);
        signModeIsOpened = true;
        textModeIsOpened = false;
        hashModeIsOpened = false;
        fileModeIsOpened = false;
        passMngrIsOpened = false;
        yandexModeIsOpened = false;
    }
}

void MainWindow::onClick_btnHashModePanel()
{
    if(hashModeIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            hashModeIsOpened = false;
        }
        clearLayout();
        hashModePanel = new HashModePanel();
        ui->verticalLayout_4->insertWidget(1, hashModePanel);
        hashModeIsOpened = true;
        fileModeIsOpened = false;
        textModeIsOpened = false;
        signModeIsOpened = false;
        passMngrIsOpened = false;
        yandexModeIsOpened = false;
    }
}

void MainWindow::clearLayout()
{
    while (QLayoutItem* item = ui->verticalLayout_4->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    fileModeIsOpened = false;
    textModeIsOpened = false;
    signModeIsOpened = false;
    hashModeIsOpened = false;
    passMngrIsOpened = false;
    yandexModeIsOpened = false;
}

void MainWindow::onClick_btnYandexModePanel()
{
    if(yandexModeIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            yandexModeIsOpened = false;
        }
        clearLayout();
        yandexModePanel = new YandexModePanel();
        ui->verticalLayout_4->insertWidget(1, yandexModePanel);
        hashModeIsOpened = false;
        fileModeIsOpened = false;
        textModeIsOpened = false;
        signModeIsOpened = false;
        passMngrIsOpened = false;
        yandexModeIsOpened = true;
    }
}

void MainWindow::onClick_btnPassMngrPanel()
{
    if(passMngrIsOpened == false)
    {
        if(ui->verticalLayout_4->count() > 0)
        {
            clearLayout();
            passMngrIsOpened = false;
        }
        clearLayout();
        passMngrPanel = new PassMngrPanel();
        ui->verticalLayout_4->insertWidget(1, passMngrPanel);
        hashModeIsOpened = false;
        fileModeIsOpened = false;
        textModeIsOpened = false;
        signModeIsOpened = false;
        yandexModeIsOpened = false;
        passMngrIsOpened = true;
    }
}

void MainWindow::showGeneratePasswordDialog()
{
    PasswordGeneratorDialog passDialog(this);
    passDialog.setWindowTitle("Генератор паролей");
    if(passDialog.exec() == QDialog::Accepted)
    {

    }
}

