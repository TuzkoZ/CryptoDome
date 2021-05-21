#ifndef GENPASSWIDGETSETTINGS_H
#define GENPASSWIDGETSETTINGS_H

#include <QWidget>

enum characterSetValues
{
    smallCharacters = 1,
    bigCharacters = 2,
    digits = 4,
    specialCharacters = 8
};

namespace Ui {
class GenPassWidgetSettings;
}

class GenPassWidgetSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GenPassWidgetSettings(QWidget *parent = nullptr);
    ~GenPassWidgetSettings();

private:
    Ui::GenPassWidgetSettings *ui;
};

#endif // GENPASSWIDGETSETTINGS_H
