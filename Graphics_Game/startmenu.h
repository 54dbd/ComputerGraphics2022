#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

namespace Ui {
class startMenu;
}

class startMenu : public QWidget
{
    Q_OBJECT

public:
    explicit startMenu(QWidget *parent = nullptr);
    ~startMenu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::startMenu *ui;
};

#endif // STARTMENU_H
