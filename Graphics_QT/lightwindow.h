#ifndef LIGHTWINDOW_H
#define LIGHTWINDOW_H

#include <QWidget>

namespace Ui {
class lightWindow;
}

class lightWindow : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
public:
    explicit lightWindow(QWidget *parent = nullptr);
    ~lightWindow();

private:
    Ui::lightWindow *ui;
    QPixmap _pixmap;//画布图片
};

#endif // LIGHTWINDOW_H
