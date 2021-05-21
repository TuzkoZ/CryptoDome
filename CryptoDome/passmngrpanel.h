#ifndef PASSMNGRPANEL_H
#define PASSMNGRPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "passmngrsettings.h"
#include "storagemngr.h"
#include "passmngrstorage.h"

namespace Ui {
class PassMngrPanel;
}

class PassMngrPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PassMngrPanel(QWidget *parent = nullptr);
    ~PassMngrPanel();

private:
    Ui::PassMngrPanel *ui;

    PassMngrSettings *passMngrSettings;
    PassMngrStorage *passMngrStorage;
    StorageMngr *storageMngr;
    QVBoxLayout *layout;

    void clearLayout(QLayout *layout);

private slots:
//    void btnNext_onClick();
//    void btnBack_onClick();
    void openStorage(StorageInfo stInfo);
};

#endif // PASSMNGRPANEL_H
