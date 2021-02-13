#ifndef FILEMODEPANEL_H
#define FILEMODEPANEL_H

#include <QWidget>

namespace Ui {
class FileModePanel;
}

class FileModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit FileModePanel(QWidget *parent = nullptr);
    ~FileModePanel();

private:
    Ui::FileModePanel *ui;
};

#endif // FILEMODEPANEL_H
