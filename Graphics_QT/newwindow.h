#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>

namespace Ui {
class newWindow;
}

class newWindow : public QWidget
{
    Q_OBJECT

public:
    QColor _color;
    Qt::PenStyle _style;
    Qt::PenCapStyle _capStyle;
    int _width;
    QPen* pen;

    explicit newWindow(QWidget *parent = nullptr);
    ~newWindow();
signals:
private slots:
    void on_pushButton_clicked();
    void getPen(QPen*);
    void on_horizontalSlider_sliderMoved(int position);

    void on_red_clicked();

    void on_blue_clicked();

    void on_yellow_clicked();

    void on_green_clicked();

    void on_black_clicked();

    void on_horizontalSlider_actionTriggered(int action);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::newWindow *ui;
};

#endif // NEWWINDOW_H
