#include "hashmodepanel.h"
#include "ui_hashmodepanel.h"

HashModePanel::HashModePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HashModePanel)
{
    ui->setupUi(this);

    connect(ui->btnBrowseFile, &QPushButton::clicked, this, &HashModePanel::onClick_btnBrowseFile);
    connect(ui->checkCompare, &QCheckBox::clicked, this, &HashModePanel::toggleCompare);
    connect(ui->btnGetHash, &QPushButton::clicked, this, &HashModePanel::onClick_btnGetHash);
}

HashModePanel::~HashModePanel()
{
    delete ui;
}

void HashModePanel::onClick_btnBrowseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leFilePath->setText(filePath);
    }
}

void HashModePanel::onClick_btnGetHash()
{
    HashManager *hashManager = new HashManager();
    QString result;

    if(ui->comboAlgorithm->currentIndex() == 0)
    {
        result = hashManager->getHash_MD4(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 1)
    {
        result = hashManager->getHash_MD5(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 2)
    {
        result = hashManager->getHash_SHA1(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 3)
    {
        result = hashManager->getHash_SHA224(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 4)
    {
        result = hashManager->getHash_SHA256(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 5)
    {
        result = hashManager->getHash_SHA384(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 6)
    {
        result = hashManager->getHash_SHA512(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 7)
    {
        result = hashManager->getHash_SHA3_224_Keccak(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 8)
    {
        result = hashManager->getHash_SHA3_256_Keccak(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 9)
    {
        result = hashManager->getHash_SHA3_384_Keccak(ui->leFilePath->text());
    }
    else if(ui->comboAlgorithm->currentIndex() == 10)
    {
        result = hashManager->getHash_SHA3_512_Keccak(ui->leFilePath->text());
    }

    ui->leResultHash->setText(result);
}

void HashModePanel::toggleCompare()
{
    if(ui->checkCompare->isChecked() == true)
    {
        ui->leCompareHash->setEnabled(true);
        ui->btnBrowsCompFile->setEnabled(true);
    }
    else
    {
        ui->leCompareHash->setEnabled(false);
        ui->btnBrowsCompFile->setEnabled(false);
    }
}
