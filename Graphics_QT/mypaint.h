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
#include "point.h"
#include <vector>
#include "TransMatrix.h"

using namespace std;

enum transform{
    NOTRANS,
    MOVE,
    ZOOM,
    ROTATE
};


extern vector<vector<pointData>> MAP;

struct arcCenter{
    int x,y;
    int R;
};

struct TransRect{
    QPoint topLeft,topRight,bottomLeft,bottomRight;
    TransRect(QPoint tl,QPoint tr,QPoint bl,QPoint br):topLeft(tl),topRight(tr),bottomLeft(bl),bottomRight(br){}
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
    int _newPolygon;//新建多边形标志
    int _drawType;//描绘类型
    QMenu *_Rmenu;//右键菜单
    int _openflag;//打开图片
    QPixmap _pixmap;//画布图片
    QPen _pen;

    QPoint referancePoint;          //变换时由用户设置的参照点
    bool isSpecificRefer = false;            //是否存在指定的参照点
    bool isInTagRect = false;
    bool isDashLine = false;
    int removeRectIndex;
    enum transform _transFlag;      //变换标志位
    QRect *transRectTag = new QRect(100,100,20,20);             //标签矩形
    QVector<QPoint> tempTransPolygon;

    int _drag;
    newWindow *setBrushWindow = new newWindow();//设置窗口

    transMatrix trans;

public:
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
    QVector<QRect> _rects;//矩形集合
    QVector<QRect> _ellipse;//椭圆集合
    QVector<QRect>  _line;//直线集合
    QVector<QRect>  _arc;//圆弧集合
    QVector<TransRect> _transRect;  //旋转矩形集合
    QVector<arcCenter> _arcCenter;
    //QVector<QRect> _secondaryCircle;//椭圆集合
    QVector<QVector<QPoint>> _polygon;//多边形集合
    QVector<QPoint> _fill;
    QRect _crop;// 裁剪的矩形

    vector<vector<QPoint>> _bezierCurve; // 若干条曲线
    vector<QPoint> _currentBezierCurve; // 当前控制点容器
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QVector<QPen> _brush;//笔刷集合
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
    //初始化
    QRect* nowRect, *nowEllipse;
    QPoint* nowFill;
    QVector<QPoint>* nowPolygon;
    int isInRect, isInEllipse,isInPolygon,isInFill;
    void circleTrans(QMouseEvent *e);
    void polygonTrans(QMouseEvent *e);
    void rectTrans(QMouseEvent *e);
    void Transform(QMouseEvent *e);
    QRect CS_ClipLine(QRect line, int XL, int XR, int YB, int YT, QPen pen);

signals:
    void sendPen(QPen*);
public slots:
    void Lines();//铅笔画线
    void SavePic();//保存图片
    void Rects();//画矩形
    void Ellipses();//画椭圆
    void Line();//画直线
    void Arc();//画圆弧
    void ArcCenter();//画圆弧圆心
    void Polygon();//画多边形
    void Fill();//填充图形
    void Bezier(); // 画贝塞尔曲线
    void Clip(); // 裁切线段
    //void SecondaryCircle();
    void OpenPic();//打开图片
    void startTrans();//开始移动物体
    void startFill();

    void createBrushWindow();

    bool polyContains(QVector<QPoint> polygon, QPoint p);
    void setDashLine(Qt::PenStyle style);

};
void Drag();
void drawRect(QRect rec,QPixmap p);
double getAngle(QPoint origin,QPoint p1,QPoint p2);
QPoint getPolyCenter(QVector<QPoint> poly);
int encode(int x, int y, int XL, int XR, int YB, int YT);
#endif // MYPAINT_H
