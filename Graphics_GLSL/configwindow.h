#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>

namespace Ui {
class configWindow;
}

class configWindow : public QWidget
{
    Q_OBJECT

public:
    explicit configWindow(QWidget *parent = nullptr);
    ~configWindow();

private slots:
    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::configWindow *ui;
    int n = 100;
    double kdks = 0.25;
signals:
    void sendValue(int n, double kdks);
};

#endif // CONFIGWINDOW_H
