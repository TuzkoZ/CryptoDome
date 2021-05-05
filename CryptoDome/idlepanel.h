#ifndef IDLEPANEL_H
#define IDLEPANEL_H

#include <QWidget>

namespace Ui {
class idlePanel;
}

class idlePanel : public QWidget
{
    Q_OBJECT

public:
    explicit idlePanel(QWidget *parent = nullptr);
    ~idlePanel();

private:
    Ui::idlePanel *ui;
};

#endif // IDLEPANEL_H
