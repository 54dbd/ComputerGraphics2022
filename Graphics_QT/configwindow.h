#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>

struct settings{
    QPen* pen;
    int* kValue;
};
namespace Ui {
class configWindow;
}

class configWindow : public QWidget
{
    Q_OBJECT

public:
    QColor _color;
    Qt::PenStyle _style;
    Qt::PenCapStyle _capStyle;
    int _width;
    QPen* pen;
    int* kValue;

    explicit configWindow(QWidget *parent = nullptr);
    ~configWindow();
signals:
    void sendStyle(Qt::PenStyle style);
private slots:
    void on_pushButton_clicked();
    void getPen(settings p);
    void on_horizontalSlider_sliderMoved(int position);

    void on_red_clicked();

    void on_blue_clicked();

    void on_yellow_clicked();

    void on_green_clicked();

    void on_black_clicked();

    void on_horizontalSlider_actionTriggered(int action);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_valueChanged(int value);

    void on_dashLine_stateChanged(int arg1);

    void on_horizontalSlider_2_rangeChanged(int min, int max);

    void on_horizontalSlider_2_sliderMoved(int position);

private:
    Ui::configWindow *ui;
};

#endif // CONFIGWINDOW_H
