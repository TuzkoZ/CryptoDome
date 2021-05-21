#ifndef PASSMNGRSETTINGS_H
#define PASSMNGRSETTINGS_H

#include <QWidget>
#include <QFileDialog>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QInputDialog>
#include <QDebug>
#include "cryptmanager.h"
#include "storagemngr.h"

struct info
{
    QString pass;
    QString masterKey;
};

enum createFlag {NONCREATE, CREATE};

namespace Ui {
class PassMngrSettings;
}

class PassMngrSettings : public QWidget
{
    Q_OBJECT

public:
    explicit PassMngrSettings(QWidget *parent = nullptr);
    ~PassMngrSettings();
    Ui::PassMngrSettings *ui;
    void setStorageMngr(StorageMngr *storageMngr);

private:
    StorageMngr *storageMngr;
    createFlag crFlag;

private slots:
    void btnBrowse_onClick();
    void btnCreate_onClick();
    void leMasterKeyChanged();
    void btnAccept_onClick();

signals:
    void accept(StorageInfo stInfo, createFlag crFlag);
};

#endif // PASSMNGRSETTINGS_H
