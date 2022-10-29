#ifndef LIGHTWINDOW_H
#define LIGHTWINDOW_H

#include <QWidget>

namespace Ui {
class lightWindow;
}

class lightWindow : public QWidget
{
    Q_OBJECT

public:
    explicit lightWindow(QWidget *parent = nullptr);
    ~lightWindow();

private:
    Ui::lightWindow *ui;
};

#endif // LIGHTWINDOW_H
