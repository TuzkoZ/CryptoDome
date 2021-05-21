#ifndef PASSMNGRSTORAGE_H
#define PASSMNGRSTORAGE_H

#include <QWidget>
#include "storagemngr.h"
#include "passrecord.h"
#include "newpassrecord.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>

namespace Ui {
class PassMngrStorage;
}

class PassMngrStorage : public QWidget
{
    Q_OBJECT

public:
    explicit PassMngrStorage(QWidget *parent = nullptr);
    ~PassMngrStorage();
    void setStorageMngr(StorageMngr storageMngr);
    void createStorage();
    void setStorageInfo(StorageInfo stInfo);

private:
    Ui::PassMngrStorage *ui;
    StorageMngr *storageMngr;
    StorageInfo stInfo;

    void updateTable(QStandardItemModel *model);


private slots:
    void updateStorageSlot();
    void btnAdd_onClick();
    void btnDel_onClick();
    void btnPassSave_onClick();
    void cellClicked();
    void btnSave_onClick();
    void addRecord(RecordInfo recInfo);
};

#endif // PASSMNGRSTORAGE_H
