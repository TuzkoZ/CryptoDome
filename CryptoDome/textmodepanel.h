#ifndef TEXTMODEPANEL_H
#define TEXTMODEPANEL_H

#include <QWidget>

namespace Ui {
class TextModePanel;
}

class TextModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit TextModePanel(QWidget *parent = nullptr);
    ~TextModePanel();

private:
    Ui::TextModePanel *ui;
};

#endif // TEXTMODEPANEL_H
