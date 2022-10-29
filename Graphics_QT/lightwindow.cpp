#include <QPainter>
#include <QPen>
#include "lightwindow.h"
#include "ui_lightwindow.h"


lightWindow::lightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lightWindow)
{
    ui->setupUi(this);
}

lightWindow::~lightWindow()
{
    delete ui;
}
void lightWindow::paintEvent(QPaintEvent *) {
    _pixmap = QPixmap(size());//新建pixmap
    _pixmap.fill(Qt::white);//背景色填充为白色
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    QPen pen;
    p.setPen(pen);
    QPoint center(300,200);
    int R = 30;
    //画圆
    Circle C(center.x(), center.y(), 0, 1, p, pen);
    C.SetR(R);
    C.DrawCircle();
}