#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnFileModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnFileModePanel);
    connect(ui->btnTextModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnTextModePanel);
    connect(ui->btnSignModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnSignModePanel);
    connect(ui->btnHashModePanel, &QPushButton::clicked, this, &MainWindow::onClick_btnHashModePanel);
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
            panelIsOpened = false;
        }
        fileModePanel = new FileModePanel();
        ui->verticalLayout_4->insertWidget(0, fileModePanel);
        fileModeIsOpened = true;
        panelIsOpened = true;
        qDebug() << "WOW";
    }
    else
    {
        clearLayout();
        fileModeIsOpened = false;
        panelIsOpened = false;
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
            panelIsOpened = false;
        }
        textModePanel = new TextModePanel();
        ui->verticalLayout_4->insertWidget(1, textModePanel);
        textModeIsOpened = true;
        qDebug() << "WOW";
    }
    else
    {
        clearLayout();
        textModeIsOpened = false;
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
            panelIsOpened = false;
        }
        signModePanel = new SignModePanel();
        ui->verticalLayout_4->insertWidget(1, signModePanel);
        signModeIsOpened = true;
        qDebug() << "WOW";
    }
    else
    {
        clearLayout();
        signModeIsOpened = false;
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
            panelIsOpened = false;
        }
        hashModePanel = new HashModePanel();
        ui->verticalLayout_4->insertWidget(1, hashModePanel);
        hashModeIsOpened = true;
        qDebug() << "WOW";
    }
    else
    {
        clearLayout();
        hashModeIsOpened = false;
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
}

