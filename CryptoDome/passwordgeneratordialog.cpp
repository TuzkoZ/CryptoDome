#include "passwordgeneratordialog.h"
#include "ui_passwordgeneratordialog.h"

PasswordGeneratorDialog::PasswordGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordGeneratorDialog)
{
    ui->setupUi(this);

    copyCloseShortcut = new QShortcut(this);
    copyCloseShortcut->setKey(Qt::CTRL + Qt::Key_X);

    connect(ui->btnStartGen, &QPushButton::clicked, this, &PasswordGeneratorDialog::btnStartGen_onClick);
    connect(ui->btnCopy, &QPushButton::clicked, this, &PasswordGeneratorDialog::btnCopy_onClick);
    connect(copyCloseShortcut, &QShortcut::activated, this, &PasswordGeneratorDialog::copyClose);
}

PasswordGeneratorDialog::~PasswordGeneratorDialog()
{
    delete ui;
}

void PasswordGeneratorDialog::btnStartGen_onClick()
{    
    ui->progressBar->setValue(0);

    int characterSet = 0;
    if(ui->chbSmallCh->isChecked())
        characterSet |= smallCharacters;
    if(ui->chbBigCh->isChecked())
        characterSet |= bigCharacters;
    if(ui->chbDigits->isChecked())
        characterSet |= digits;
    if(ui->chbSpecialChar->isChecked())
        characterSet |= specialCharacters;
    if(characterSet == 0)
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка");
        msg.setText("Необходимо выбрать набор символов");
        msg.exec();
    }
    else
    {
        if(generator == nullptr)
        {
            generator = new GraphicGenerator(ui->progressBar, this);
            generator->setMaximumSize(IMAGE_WIDTH, IMAGE_HEIGHT);
            generator->setMinimumSize(IMAGE_WIDTH, IMAGE_HEIGHT);
            generator->setMouseTracking( true );

            QVBoxLayout *vlayout = new QVBoxLayout();
            vlayout->addWidget(generator);
            ui->genWidget->setLayout(vlayout);
        }
        generator->initGenerator(ui->sbLength->value(), characterSet);
        connect(generator, SIGNAL(generatingEnd()), this, SLOT(genEnd()));
    }
}

void PasswordGeneratorDialog::genEnd()
{
    ui->leResult->setText(generator->getResult());
}

void PasswordGeneratorDialog::btnCopy_onClick()
{
    QClipboard *bufer = QApplication::clipboard();
    bufer->setText(ui->leResult->text());
}

void PasswordGeneratorDialog::copyClose()
{
    QClipboard *bufer = QApplication::clipboard();
    bufer->setText(ui->leResult->text());
    this->close();
}
