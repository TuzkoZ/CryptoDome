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
    connect(ui->btnBrowsCompFile, &QPushButton::clicked, this, &HashModePanel::onClick_btnBrowseCompareFile);
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
    QString resultComp;
    QString currentAlgorithm;
    bool isDifferent = false;

    //Проверка, что пути к файлам заполнены
    if(ui->checkCompare->isChecked() == false)
    {
        if(ui->leFilePath->text().isEmpty() == true)
        {
            showMsg("Ошибка заполнения", "Путь к файлу не должен быть пустым");
            return;
        }
        else
        {
            QFileInfo fileInfo(ui->leFilePath->text());
            if(fileInfo.exists() && fileInfo.isFile())
            {

            }
            else
            {
                showMsg("Ошибка выбора файла", "Файл не был найден или не может быть открыт");
                return;
            }
        }
    }
    else
    {
        if(ui->leFilePath->text().isEmpty() == true || ui->leCompareHash->text().isEmpty() == true)
        {
            showMsg("Ошибка заполнения", "Путь к файлу не должен быть пустым");
            return;
        }
        else
        {
            QFileInfo fileInfo1(ui->leFilePath->text());
            QFileInfo fileInfo2(ui->leCompareHash->text());
            if(fileInfo1.exists() && fileInfo1.isFile() && fileInfo2.exists() && fileInfo2.isFile())
            {

            }
            else
            {
                showMsg("Ошибка выбора файла", "Файл не был найден или не может быть открыт");
                return;
            }
        }
    }
    //

    if(ui->comboAlgorithm->currentIndex() == 0)
    {
        currentAlgorithm = "MD4";
        result = hashManager->getHash_MD4(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_MD4(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 1)
    {
        currentAlgorithm = "MD5";
        result = hashManager->getHash_MD5(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_MD5(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 2)
    {
        currentAlgorithm = "SHA1";
        result = hashManager->getHash_SHA1(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA1(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 3)
    {
        currentAlgorithm = "SHA224";
        result = hashManager->getHash_SHA224(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA224(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 4)
    {
        currentAlgorithm = "SHA256";
        result = hashManager->getHash_SHA256(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA256(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 5)
    {
        currentAlgorithm = "SHA384";
        result = hashManager->getHash_SHA384(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA384(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 6)
    {
        currentAlgorithm = "SHA512";
        result = hashManager->getHash_SHA512(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA512(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 7)
    {
        currentAlgorithm = "SHA3_224_Keccak";
        result = hashManager->getHash_SHA3_224_Keccak(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA3_224_Keccak(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 8)
    {
        currentAlgorithm = "SHA3_226_Keccak";
        result = hashManager->getHash_SHA3_256_Keccak(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA3_256_Keccak(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 9)
    {
        currentAlgorithm = "SHA3_384_Keccak";
        result = hashManager->getHash_SHA3_384_Keccak(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA3_384_Keccak(ui->leCompareHash->text());
        }
    }
    else if(ui->comboAlgorithm->currentIndex() == 10)
    {
        currentAlgorithm = "SHA3_512_Keccak";
        result = hashManager->getHash_SHA3_512_Keccak(ui->leFilePath->text());
        if(ui->checkCompare->isChecked() == true)
        {
            resultComp = hashManager->getHash_SHA3_512_Keccak(ui->leCompareHash->text());
        }
    }

    ui->leResultHash->setText(result);
    if(ui->checkCompare->isChecked() == true)
    {
        if(result == resultComp)
        {
            isDifferent = false;
            showMsg("Результат сравнения", "Хэш суммы файлов совпадают");
        }
        else
        {
            isDifferent = true;
            showMsg("Результат сравнения", "Хэш суммы файлов различаются");
        }
    }

    if(ui->checkSaveTxt->isChecked() == true)
    {
        if(ui->checkCompare->isChecked() == false)
        {
            QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Текстовый файл (*.txt)"));
            if(filePath.isEmpty() != true)
            {
                QFile resultFile(filePath);
                if(resultFile.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream writeStream(&resultFile);
                    writeStream << QDate::currentDate().toString() << " | " << QTime::currentTime().toString() <<"\n";
                    writeStream << "Algorithm: " << "[" << currentAlgorithm << "]" << "\n";
                    writeStream << "File: " << ui->leFilePath->text() << "\n";
                    writeStream << "Hash: " << result << "\n\n";

                }
                resultFile.close();
            }
        }
        else
        {
            QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"), "", tr("Текстовый файл (*.txt)"));
            if(filePath.isEmpty() != true)
            {
                QFile resultFile(filePath);
                if(resultFile.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream writeStream(&resultFile);
                    writeStream << QDate::currentDate().toString() << " | " << QTime::currentTime().toString() <<"\n";
                    writeStream << "Algorithm: " << "[" << currentAlgorithm << "]" << "\n";
                    writeStream << "File1: " << ui->leFilePath->text() << "\n";
                    writeStream << "Hash: " << result << "\n";
                    writeStream << "File2: " << ui->leCompareHash->text() << "\n";
                    writeStream << "Hash: " << resultComp << "\n";
                    if(isDifferent == false)
                    {
                        writeStream << "Result of comparison: files are not different" << "\n\n";
                    }
                    else
                    {
                        writeStream << "Result of comparison: files are different" << "\n\n";
                    }
                }
                resultFile.close();
            }
        }


    }
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

void HashModePanel::onClick_btnBrowseCompareFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), "", tr("Все файлы (*)"));
    if(!filePath.isEmpty())
    {
        ui->leCompareHash->setText(filePath);
    }
}

void HashModePanel::showMsg(QString title, QString msg)
{
    QMessageBox winMsg;
    winMsg.setWindowTitle(title);
    winMsg.setText(msg);
    winMsg.exec();
}

void HashModePanel::saveResult()
{

}
