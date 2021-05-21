#ifndef GENPASSWIDGET_H
#define GENPASSWIDGET_H

#include <QWidget>

namespace Ui {
class GenPassWidget;
}

class GenPassWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GenPassWidget(QWidget *parent = nullptr);
    ~GenPassWidget();

private:
    Ui::GenPassWidget *ui;
};

#endif // GENPASSWIDGET_H
