#ifndef MYPAINT_H
#define MYPAINT_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include "newwindow.h"
struct arcCenter{
    int x,y;
    int R;
};
class MyPaint : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyPaint(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void contextMenuEvent(QContextMenuEvent *);//重写菜单事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件
public:
private:
    int _lpress;//左键按下标志
    int _secCircle;//辅助圆标志
    int _drawType;//描绘类型
    QMenu *_Rmenu;//右键菜单
    int _openflag;//打开图片
    QPixmap _pixmap;//画布图片
    QPen _pen;

    newWindow *setBrushWindow = new newWindow();//设置窗口


public:
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
    QVector<QRect> _rects;//矩形集合
    QVector<QRect> _ellipse;//椭圆集合
    QVector<QRect>  _line;//直线集合
    QVector<QRect>  _arc;//圆弧集合
    QVector<arcCenter> _arcCenter;
    //QVector<QRect> _secondaryCircle;//椭圆集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
signals:
    void sendPen(QPen*);
public slots:
    void Lines();//铅笔画线
    void SavePic();//保存图片
    void Rects();//画矩形
    void Ellipses();//画椭圆
    void Line();//画直线
    void Arc();//画圆弧
    void ArcCenter();
    //void SecondaryCircle();
    void OpenPic();//打开图片
    void createBrushWindow();




};

#endif // MYPAINT_H
