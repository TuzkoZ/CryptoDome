#ifndef NEWPASSRECORD_H
#define NEWPASSRECORD_H

#include <QWidget>
#include <QString>

struct RecordInfo
{
    QString name;
    QString URL;
    QString login;
    QString password;
    QString description;
};

namespace Ui {
class NewPassRecord;
}

class NewPassRecord : public QWidget
{
    Q_OBJECT

public:
    explicit NewPassRecord(QWidget *parent = nullptr);
    ~NewPassRecord();

private:
    Ui::NewPassRecord *ui;

private slots:
    void btnAdd_onClick();

signals:
    void accept(RecordInfo recInfo);
};

#endif // NEWPASSRECORD_H
