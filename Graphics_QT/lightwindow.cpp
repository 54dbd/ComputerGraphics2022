#include <QPainter>
#include <QPen>
#include "lightwindow.h"
#include "ui_lightwindow.h"

lightWindow::lightWindow(QWidget *parent) :
        QWidget(parent),
    ui(new Ui::lightWindow)
{
    this->setGeometry(350, 200, 600, 400);//设置窗体大小、位置
    setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
    this->setStyleSheet("background-color:white;");
    ui->setupUi(this);
}

lightWindow::~lightWindow()
{
    delete ui;
}
void lightWindow::paintEvent(QPaintEvent *) {
    qDebug()<<"painting";


    _pixmap = QPixmap(size());//新建pixmap
    _pixmap.fill(Qt::white);//背景色填充为白色
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    QPen pen;
    Brush b(1,p,pen);
    b.drawPixel(100,100);
    QPoint center(100,100);
    int R = 30;
    //画圆
    Circle C(center.x(), center.y(), 0, 5, p, pen);
    C.SetR(R);
    C.DrawCircle();
}