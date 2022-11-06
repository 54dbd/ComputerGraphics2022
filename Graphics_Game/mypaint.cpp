#include "mypaint.h"

#include "Arc.h"
#include "Polygon.h"
#include "Bezier.h"
#include "Fill.h"
#include <QDebug>
#include <iostream>
#include <QRect>
#include <QLabel>
#include <QStatusBar>
#include "configwindow.h"
#include "utils.h"
#include "Line.h"
#include "Circle.h"
#include <QTimer>
using namespace std;
vector<vector<pointData>> MAP;

MyPaint::MyPaint(QWidget *parent) :
        QMainWindow(parent) {
    _lpress = false;//初始鼠标左键未按下
    _newPolygon = true;//代表多边形可以新建
    _drag = 0;//默认非拖拽模式
    _drawType = 0;//初始为什么都不画
    _begin = pos();//拖拽的参考坐标，方便计算位移
    _openflag = 0;//初始不打开图片
    _transFlag = NOTRANS;

    this->setGeometry(350, 200, 600, 400);//设置窗体大小、位置
    this->setFixedSize(600, 400);
//    setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
    this->setStyleSheet("background-color:white;");
    //初始化MAP
    initMAP();

    //创建工具栏
    tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(16, 16));//设置动作图标的尺寸
    tbar->setStyleSheet("background-color:white");//背景色

    _Rmenu = new QMenu(this);//创建右键菜单
    _Rmenu->addAction(tr("保存  \tCtrl+S"), this, SLOT(SavePic()));//添加菜单动作
    _Rmenu->addAction(tr("退出  \tALT+F4"), this, SLOT(close()));//添加菜单动作
    _Rmenu->setStyleSheet("background-color:white");//设置背景色

    //笔刷颜色
    QAction *setBrush = new QAction(tr("&笔刷"), this);
    tbar->addAction(setBrush);

    QAction *clean = new QAction(tr("&清除"), this);
    tbar->addAction(clean);

    QAction *openAction = new QAction(tr("&打开"), this);//打开动作
    openAction->setIcon(QIcon(":/png/images/open.png"));//图标
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
    tbar->addAction(openAction);//添加到工具栏

    QAction *saveAction = new QAction(tr("&保存"), this);//保存动作
    saveAction->setIcon(QIcon(":/png/images/save.png"));//图标
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//热键
    tbar->addAction(saveAction);//添加到工具栏

    QAction *saveasAction = new QAction(tr("&另存为"), this);//保存动作
    saveasAction->setIcon(QIcon(":/png/images/saveas.png"));//图标
    saveasAction->setShortcut(QKeySequence(tr("Ctrl+ALT+S")));//热键
    tbar->addAction(saveasAction);//添加到工具栏

    QAction *transAction = new QAction(tr("&图形变换"), this); /**变换动作**/
    transAction->setIcon(QIcon(":/png/images/trans.png"));//图标
    tbar->addAction(transAction);//添加到工具栏

    QAction *fillAction = new QAction(tr("&填充"), this);//填充
    fillAction->setIcon(QIcon(":/png/images/fill.png"));//图标
    tbar->addAction(fillAction);//添加到工具栏

    QAction *lineAction = new QAction(tr("&直线"), this);//直线动作
    lineAction->setIcon(QIcon(":/png/images/line.png"));//图标
    lineAction->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
    tbar->addAction(lineAction);//添加到工具栏

    QAction *linesAction = new QAction(tr("&铅笔"), this);//铅笔动作
    linesAction->setIcon(QIcon(":/png/images/lines.png"));//图标
    linesAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
    tbar->addAction(linesAction);//添加到工具栏

    QAction *rectAction = new QAction(tr("&矩形"), this);//矩形动作
    rectAction->setIcon(QIcon(":/png/images/rect.png"));//图标
    rectAction->setShortcut(QKeySequence(tr("Ctrl+R")));//热键
    tbar->addAction(rectAction);

    QAction *ellipseAction = new QAction(tr("&椭圆"), this);//椭圆动作
    ellipseAction->setIcon(QIcon(":/png/images/ellipse.png"));//图标
    ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
    tbar->addAction(ellipseAction);

    QAction *arcAction = new QAction(tr("&圆弧"), this);//圆弧动作
    arcAction->setIcon(QIcon(":/png/images/arc.png"));//图标
    arcAction->setShortcut(QKeySequence(tr("Ctrl+A")));//热键
    tbar->addAction(arcAction);

    QAction *arcCenterAction = new QAction(tr("&圆弧圆心"), this);//圆弧动作
    arcCenterAction->setIcon(QIcon(":/png/images/arcCenter.png"));//图标
    arcCenterAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
    tbar->addAction(arcCenterAction);

    QAction *polygonAction = new QAction(tr("&多边形"), this);//多边形动作
    polygonAction->setIcon(QIcon(":/png/images/polygon.png"));//图标
    tbar->addAction(polygonAction);

    QAction *bezierAction = new QAction(tr("&贝塞尔"), this);//贝塞尔
    bezierAction->setIcon(QIcon(":/png/images/bezier.png"));//图标
    tbar->addAction(bezierAction);

    QAction *bsplineAction = new QAction(tr("&B样条"), this);
//    bsplineAction->setIcon(QIcon(":/png/images/bspline.png"));//图标
    tbar->addAction(bsplineAction);

    QAction *clipAction = new QAction(tr("&裁切线段"), this);//裁切线段
    tbar->addAction(clipAction);



    QAction *clipPolygon = new QAction(tr("&裁切多边形"), this);//裁切多边形
    tbar->addAction(clipPolygon);

    //创建底部状态栏
    statusBarLabel = new QLabel("当前坐标：", this);
    statusBarLabel->setMinimumWidth(250);
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->addWidget(statusBarLabel);
    statusBar->setGeometry(0, 380, 600, 20);
    statusBar->setStyleSheet("border: solid black 2px;");



    //创建一个计时器来更新每个fream
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(next_frame()));
    timer->start(10);


    //连接信号与槽函数
    connect(linesAction, SIGNAL(triggered()), this, SLOT(Lines()));
    connect(rectAction, SIGNAL(triggered()), this, SLOT(Rects()));
    connect(ellipseAction, SIGNAL(triggered()), this, SLOT(Ellipses()));
    connect(lineAction, SIGNAL(triggered()), this, SLOT(Line()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
    connect(arcAction, SIGNAL(triggered()), this, SLOT(Arc()));
    connect(arcCenterAction, SIGNAL(triggered()), this, SLOT(ArcCenter()));
    connect(polygonAction, SIGNAL(triggered()), this, SLOT(Polygon()));
    connect(bezierAction, SIGNAL(triggered()), this, SLOT(Bezier()));
    connect(bsplineAction, SIGNAL(triggered()), this, SLOT(Bspline()));
    connect(clipAction, SIGNAL(triggered()), this, SLOT(Clip()));
    connect(clipPolygon, SIGNAL(triggered()), this, SLOT(ClipPolygon()));
    connect(clean, SIGNAL(triggered()), this, SLOT(cleanScreen()));


    connect(transAction, SIGNAL(triggered()), this, SLOT(startTrans()));
    connect(fillAction, SIGNAL(triggered()), this, SLOT(startFill()));
    //新建界面
    connect(setBrush, SIGNAL(triggered()), this, SLOT(createBrushWindow()));

    //设置界面传参
    connect(this, SIGNAL(sendPen(QPen * )), setBrushWindow, SLOT(getPen(QPen * )));
    connect(setBrushWindow, SIGNAL(sendStyle(Qt::PenStyle)), this, SLOT(setDashLine(Qt::PenStyle)));


}

void MyPaint::next_frame(){
    if (playerY >= 350) {
        _playerStatus = DIE;
        showMessageBox();
    }
    update();
}

void MyPaint::paintEvent(QPaintEvent *) {
    if (_playerStatus == DIE){
        return;
    }
    if (_openflag == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        _pixmap = QPixmap(size());//新建pixmap
        _pixmap.fill(Qt::white);//背景色填充为白色
    }
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    //QPainter p=_pen;//将_pixmap作为画布

    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0, i9 = 0, i11 = 0, i13 = 0;//各种图形的索引

    QPen pen;
    pen.setColor(Qt::black);

    // 设置玩家初始状态
    _playerStatus = ALIVE;
    //重力影响
    if(canDrop(playerX,playerY)){
        playerY+=1;
    }
    //创建关卡
    _stage = new Stage(1,p,pen,playerX,playerY,state,_updateCount);

//    if(playerY>300)
//        playerY=300;
    pen.setColor(Qt::black);
    pen.setWidth(5);
    class Line l(0,300,600,300,1,p,pen);
    l.MidPoint();
    _updateCount++;
//    _stage->nextFrame();
//    qDebug()<<"count: "<<(_updateCount++/20)%4;
//    qDebug()<<"state:"<<state;
    if (_drawType == 10) {  //绘制标志矩形与自定义参考点

        QPoint start, end;
        start = transRectTag->topLeft();
        end = transRectTag->bottomRight();
        int x_s = start.x();
        int x_e = end.x();
        int y_s = start.y();
        int y_e = end.y();
        QPen pen;
        //创建直线
        class Line l1(x_s, y_s, x_e, y_s, 1, p, pen);
        class Line l2(x_s, y_s, x_s, y_e, 1, p, pen);
        class Line l3(x_e, y_e, x_s, y_e, 1, p, pen);
        class Line l4(x_e, y_e, x_e, y_s, 1, p, pen);
        l1.MidPoint();
        l2.MidPoint();
        l3.MidPoint();
        l4.MidPoint();

        if (isSpecificRefer) {
            for (int i = referancePoint.x() - 3; i < referancePoint.x() + 4; ++i) {
                Brush b(1, p, pen);
                b.drawPixel(i, referancePoint.y());
            }
            for (int i = referancePoint.y() - 3; i < referancePoint.y() + 4; ++i) {
                Brush b(1, p, pen);
                b.drawPixel(referancePoint.x(), i);
            }
        }
    }

    for (int c = 0; c < _shape.size(); ++c)//控制用户当前所绘图形总数
    {
        // 获取对应的笔刷颜色，并设置
        QPen pen = _brush.at(c);
        p.setPen(pen);
        if (_shape.at(c) == 1)//线条
        {
            const QVector<QPoint> &line = _lines.at(i1++);//取出一条线条
            pen.setWidth(5);
            for (int j = 0; j < line.size() - 1; ++j)//将线条的所有线段描绘出
            {

                int x_s = line.at(j).x();
                int x_e = line.at(j + 1).x();
                int y_s = line.at(j).y();
                int y_e = line.at(j + 1).y();
                class Line l(x_s, y_s, x_e, y_e, 1, p, pen);
                if (pen.style() == Qt::DashLine)
                    l.DashLine();
                else
                    l.MidPoint();
            }
        } else if (_shape.at(c) == 2)//矩形
        {
            QPoint start, end;
            start = _rects.at(i2).topLeft();
            end = _rects.at(i2).bottomRight();
            int x_s = start.x();
            int x_e = end.x();
            int y_s = start.y();
            int y_e = end.y();
            //创建直线
            class Line l1(x_s, y_s, x_e, y_s, 1, p, pen);
            class Line l2(x_s, y_s, x_s, y_e, 1, p, pen);
            class Line l3(x_e, y_e, x_s, y_e, 1, p, pen);
            class Line l4(x_e, y_e, x_e, y_s, 1, p, pen);
            if (!_lpress) {//松开时
                if (pen.style() == Qt::DashLine) {
                    l1.DashLine();
                    l2.DashLine();
                    l3.DashLine();
                    l4.DashLine();
                } else {
                    l1.MidPoint();
                    l2.MidPoint();
                    l3.MidPoint();
                    l4.MidPoint();
                }

            } else {//按住时
                if (pen.style() == Qt::DashLine) {
                    l1.dashLineNoMap();
                    l2.dashLineNoMap();
                    l3.dashLineNoMap();
                    l4.dashLineNoMap();
                } else {
                    l1.MidPointNoMap();
                    l2.MidPointNoMap();
                    l3.MidPointNoMap();
                    l4.MidPointNoMap();
                }

            }


            i2++;
        } else if (_shape.at(c) == 3)//正圆
        {
            QPoint center;
            center = _ellipse.at(i3).center();
            int R = abs(center.y() - _ellipse.at(i3).bottom());

            //画圆
            Circle C(center.x(), center.y(), 0, 1, p, pen);
            C.SetR(R);
            if (pen.style() == Qt::DashLine)
                C.DrawDashLIneCircle();
            else
                C.DrawCircle();
            i3++;
        } else if (_shape.at(c) == 4)//直线
        {
            QPoint start, end;
            start = _line.at(i4).topLeft();
            end = _line.at(i4).bottomRight();
            int x_s = start.x();
            int x_e = end.x();
            int y_s = start.y();
            int y_e = end.y();
            //创建直线
            class Line l(x_s, y_s, x_e, y_e, 1, p, pen);
            if (pen.style() == Qt::DashLine)
                l.DashLine();
            else
                l.MidPoint();
            i4++;

        } else if (_shape.at(c) == 5) {

            //画圆弧
            //_secCircle=0;
            QPoint start, end;
            struct arcCenter center;
            start = _arc.at(i5).topLeft();
            end = _arc.at(i5).bottomRight();
            int x_s = start.x();
            int y_s = start.y();


            center = _arcCenter.at(i5);
            center.R = sqrt((x_s - center.x) * (x_s - center.x) + (y_s - center.y) * (y_s - center.y));
            //圆弧圆心

            //使圆心不受笔刷大小影响
            QPen temp = pen;
            pen.setWidth(1);
            p.setPen(pen);

            Brush b(3, p, pen);
            if (i5 == _arcCenter.length() - 1)//只保留最后一个
                b.drawPixel(center.x, center.y);

            //恢复笔刷大小
            pen = temp;
            p.setPen(pen);

            class Arc a(center.x, center.y, center.R, 1, p, pen);
            a.DrawArc(start.x(), start.y(), end.x(), end.y());

            i5++;


        } else if (_shape.at(c) == 6) {

        } else if (_shape.at(c) == 7) { // 绘制多边形
            const QVector<QPoint> &polygon = _polygon.at(i7++);//取出一个多边形
            class Polygon poly(1, p, this->screen()->size().height(), pen);
            for (int j = 0; j < polygon.size(); ++j)//将多边形的所有线段描绘出
            {
                int temp = (j + 1) % int(polygon.size());
                int x_s = polygon.at(j).x();
                int x_e = polygon.at(temp).x();
                int y_s = polygon.at(j).y();
                int y_e = polygon.at(temp).y();
                Edge *e = new Edge(x_s, y_s, x_e, y_e);
                poly.addEdgeToET(e);
            }
            poly.drawPolygon();
        } else if (_shape.at(c) == 8) {
            // 绘制裁切多边形的窗口
            for (int j = 0; j < _cropPolygon.size(); ++j)//将多边形的所有线段描绘出
            {
                int temp = (j + 1) % int(_cropPolygon.size());
                int x_s = _cropPolygon.at(j).x();
                int x_e = _cropPolygon.at(temp).x();
                int y_s = _cropPolygon.at(j).y();
                int y_e = _cropPolygon.at(temp).y();
                class Line l(x_s, y_s, x_e, y_e, 1, p, pen);
                l.DashLine();
            }
        } else if (_shape.at(c) == 9) { // bezier
            const vector<QPoint> &bezierCurve = _bezierCurve.at(i9++);

            //使控制点不受笔刷大小影响
            QPen temp = pen;
            pen.setWidth(1);
            p.setPen(pen);

            Brush t_brush(3, p, pen);

            // 画控制点
            for (auto i: bezierCurve) {
                Circle C(i.x(), i.y(), 4, 1, p, pen);
                C.DrawCircle();
            }
            class Bezier b(1, p, bezierCurve, pen);
            b.drawBezier();

            for (auto &i: _currentBezierCurve) {
                Circle C(i.x(), i.y(), 4, 1, p, pen);
                C.DrawCircle();
            }

            //恢复笔刷大小
            pen = temp;
            p.setPen(pen);
        } else if (_shape.at(c) == 13) { // bspline
            const vector<QPoint> &bsplineCurve = _bsplineCurve.at(i13++);

            //使控制点不受笔刷大小影响
            QPen temp = pen;
            pen.setWidth(1);
            p.setPen(pen);

            Brush t_brush(3, p, pen);

            // 画控制点
            for (auto i: bsplineCurve) {
                Circle C(i.x(), i.y(), 4, 1, p, pen);
                C.DrawCircle();
            }
            // 需要交互设置k阶 目前设置为3
            int temp_k = 3;
            class Bspline b(1, p, bsplineCurve, temp_k, pen);
            b.drawBspline();

            for (auto &i: _currentBsplineCurve) {
                Circle C(i.x(), i.y(), 4, 1, p, pen);
                C.DrawCircle();
            }

            //恢复笔刷大小
            pen = temp;
            p.setPen(pen);
        } else if (_shape.at(c) == 11) {//fill
            class Fill f(pix, p, pen);
//            f.fillColor(Qt::blue);
            //f.fillRect(*nowRect);
            //DEBUG: test rect for all the shape
            //
//            QPoint p;
            qDebug() << "[paintEvent]filling i11[ " << i11 << " ]";
            f.getColorMap();
            f.fillShape(_fill.at(i11), pen.color());
            i11++;
//            f.restoreColor();
//            if(isInRect){
//                //f.fillRect(*nowRect);
//                //f.restoreColor();
//            }else if (isInEllipse){

//            }else if(isInPolygon){

//            }

        } else if (_shape.at(c) == 12)//显示裁切矩形
        {
            QPoint start, end;
            start = _crop.topLeft();
            end = _crop.bottomRight();
            int x_s = start.x();
            int x_e = end.x();
            int y_s = start.y();
            int y_e = end.y();
            //创建直线
            class Line l1(x_s, y_s, x_e, y_s, 1, p, pen);
            class Line l2(x_s, y_s, x_s, y_e, 1, p, pen);
            class Line l3(x_e, y_e, x_s, y_e, 1, p, pen);
            class Line l4(x_e, y_e, x_e, y_s, 1, p, pen);
            if (_lpress) { //按住时
                l1.dashLineNoMap();
                l2.dashLineNoMap();
                l3.dashLineNoMap();
                l4.dashLineNoMap();
            }
        }
    }

    if (!_currentBezierCurve.empty() || !_currentBsplineCurve.empty()) {
        QPen pen = _pen;
        p.setPen(pen);
        QPen temp = pen;
        pen.setWidth(1);
        p.setPen(pen);
        Brush t_brush(3, p, pen);
        // 画控制点
        for (auto &i: _currentBezierCurve) {
            Circle C(i.x(), i.y(), 4, 1, p, pen);
            C.DrawCircle();
        }
        for (auto &i: _currentBsplineCurve) {
            Circle C(i.x(), i.y(), 4, 1, p, pen);
            C.DrawCircle();
        }
        //恢复笔刷大小
        pen = temp;
        p.setPen(pen);
    }

    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0, 0, pix);//将pixmap画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent *e) {

    if (e->button() == Qt::MiddleButton) {
        if (_drawType == 10) {
            referancePoint = e->pos();
            isSpecificRefer = true;
            update();
        }
    }

    if (e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        qDebug() << "_brushSize:" << _brush.length();
        qDebug() << "_shapeSize:" << _shape.length();

        _drag = 0;
        QPen tempPen(_pen);
        if (_drawType == 10) {//移动
            update();
            _drag = 1;
            qDebug() << "drag:" << _drag;

        }
        if (_drawType == 7)//多边形处理笔刷
        {
            qDebug() << "drawing polygon";
            tempPen.setWidth(1);
        }
            // 防止Bezier/spline或者移动操作 每新建一个点，就会添加一个笔刷，造成笔刷数组中存在大量的多余笔刷，导致修改颜色失效
        else if (_drawType == 0 || _drawType == 9 || _drawType == 13 || _drawType == 10) { // Bezier & move
            qDebug() << "drawing bezier";
            qDebug() << "drawing bspline";
            qDebug() << "moving shape";
        } else {
            _brush.append(tempPen);//将当前笔刷颜色加入到笔刷颜色列表中

        }

        if (_drawType == 1)//线条(铅笔)
        {
            _lpress = true;//左键按下标志
            QVector<QPoint> line;//鼠标按下，新的线条开始
            _lines.append(line);//将新线条添加到线条集合
            QVector<QPoint> &lastLine = _lines.last();//拿到新线条
            lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
            _shape.append(1);
        } else if (_drawType == 2 || (_drawType == 10 && isInRect))//矩形
        {
            _lpress = true;//左键按下标志

            if (!_drag) {
                qDebug() << "new rect";
                QRect rect;//鼠标按下，矩形开始
                _rects.append(rect);//将新矩形添加到矩形集合
                QRect & lastRect = _rects.last();//拿到新矩形
                lastRect.setTopLeft(e->pos());//记录鼠标的坐标(新矩形的左上角坐标)
                _shape.append(2);
            } else {
                //寻找当前是哪个图形
                if (isInRect) {
                    _begin = e->pos();
                    qDebug() << "found the rect";
                }
            }
        } else if (_drawType == 3 || (_drawType == 10 && isInEllipse))//椭圆
        {
            _lpress = true;//左键按下标志

            if (!_drag) {
                QRect rect;//鼠标按下，椭圆开始
                qDebug() << "new ellipse";
                _ellipse.append(rect);//将新椭圆添加到椭圆集合
                QRect & lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                _shape.append(3);
            } else {
                qDebug() << "isInEllipse" << isInEllipse;
                if (isInEllipse) {
                    _begin = e->pos();
                    qDebug() << "found the ellipse";

                }
            }


        } else if (_drawType == 4)//直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line.append(rect);//将新直线添加到直线集合
            QRect & lastLine = _line.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(4);
        } else if (_drawType == 5)//圆弧
        {
            if (_arcCenter.length() == 0)
                return;
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，正圆开始

            qDebug("_arc.appending...");
            _arc.append(rect);//将新正圆添加到椭圆集合
            QRect & lastArc = _arc.last();//拿到新圆弧
            lastArc.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
            if (_arcCenter.length() < _arc.length()) {//如果出现了在一个圆心上重复画弧的情况，就复制一个最后一个圆弧心
                struct arcCenter center;
                center.x = _arcCenter.last().x;
                center.y = _arcCenter.last().y;
                _arcCenter.append(center);
            }

            _shape.append(5);
        } else if (_drawType == 6) {//圆弧圆心
            struct arcCenter center;
            center.x = e->pos().x();
            center.y = e->pos().y();
            _arcCenter.append(center);
            qDebug() << "center at" << center.x << "," << center.y;
        } else if (_drawType == 7 || (_drawType == 10 && isInPolygon)) { // 绘制多边形
            _lpress = true;//左键按下标志
            if (!_drag) {
                if (_newPolygon == true) {
                    // 创建一个新的多边形
                    QVector<QPoint> polygon;
                    //                QPen tempPen(_pen);
                    //强制改变多边形画笔粗细
                    tempPen.setWidth(1);
                    _brush.append(tempPen);
                    _polygon.append(polygon);
                    _shape.append(7);
                    _newPolygon = false;
                }
                // 拿到最后一个多边形的数组
                QVector<QPoint> &lastPolygon = _polygon.last();
                // 创建点
                QPoint a;
                a.setX(e->pos().x());
                a.setY(e->pos().y());
                qDebug() << "x:" << a.x() << "y:" << a.y();
                // 将新的点添加到多边形集合
                lastPolygon.append(a);
            } else {
                qDebug() << "isInPolygon" << isInPolygon;
                if (isInPolygon) {
                    _begin = e->pos();
                    qDebug() << "found the polygon";
                }
            }
        } else if (_drawType == 8) {
            // 裁切多边形
            QPoint a;
            a.setX(e->pos().x());
            a.setY(e->pos().y());
            // 将点击的点添加到裁切多边形窗口的容器中
            _cropPolygon.append(a);
            _shape.append(8);
            update();
        } else if (_drawType == 9 || (_drawType == 10)) {// beizer的绘制和bezier/bspline的控制点定位
            _lpress = true;
            if (!_drag) {
                QPoint p(e->pos().x(), e->pos().y());
                _currentBezierCurve.push_back(p);
                qDebug() << "x:" << e->pos().x() << "y:" << e->pos().y();
            }
            for (int i = 0; i < _bezierCurve.size(); ++i) {
                for (int j = 0; j < _bezierCurve[i].size(); ++j) {
                    // 判断当前点是否在控制点的圆内
                    if (e->pos().x() <= _bezierCurve[i][j].x() + 10 && e->pos().x() >= _bezierCurve[i][j].x() - 10 &&
                        e->pos().y() <= _bezierCurve[i][j].y() + 10 && e->pos().y() >= _bezierCurve[i][j].y() - 10) {
                        nowControlPoint = &_bezierCurve[i][j];
                    }
                }
            }
            for (int i = 0; i < _bsplineCurve.size(); ++i) {
                for (int j = 0; j < _bsplineCurve[i].size(); ++j) {
                    // 判断当前点是否在控制点的圆内
                    if (e->pos().x() <= _bsplineCurve[i][j].x() + 10 && e->pos().x() >= _bsplineCurve[i][j].x() - 10 &&
                        e->pos().y() <= _bsplineCurve[i][j].y() + 10 && e->pos().y() >= _bsplineCurve[i][j].y() - 10) {
                        nowControlPoint = &_bsplineCurve[i][j];
                    }
                }
            }
        } else if (_drawType == 13) {// bspline
            _lpress = true;
            if (!_drag) {
                QPoint p(e->pos().x(), e->pos().y());
                _currentBsplineCurve.push_back(p);
                qDebug() << "x:" << e->pos().x() << "y:" << e->pos().y();
            }
        } else if (_drawType == 11) {//fill
            _lpress = true;
            QPoint pos = e->pos();
            _fill.append(pos);
            qDebug() << "start fill at" << pos.x() << ", " << pos.y();
            _shape.append(11);
        } else if (_drawType == 12) {
            _lpress = true;//左键按下标志
            _crop.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(12);
        }
    }
}


void MyPaint::mouseMoveEvent(QMouseEvent *e) {

    isInFill = 0;
    isInTagRect = false;
    int isArrow = 1;
    //定位鼠标指到的图形
    updateCoordiante(e->pos().x(), e->pos().y());
    if (_rects.length() > 0) {
        for (int i = 0; i < _rects.length(); i++) {
            if (_rects.at(i).contains(e->pos())) {
                removeRectIndex = i;
                nowRect = &_rects[i];
                isInRect = 1;
                isInPolygon = 0;
                isInEllipse = 0;
                isArrow = 0;
                for (int j = 0; j < _fill.length(); j++) {
                    if (_rects.at(i).contains(_fill.at(j))) {
                        nowFill = &_fill[j];
                        isInFill = 1;
                    }
                }
//                qDebug()<<"now in rect["<<i<<"]";
            }
        }
    }
    if (_ellipse.length() > 0) {
        for (int i = 0; i < _ellipse.length(); i++) {
            if (_ellipse.at(i).contains(e->pos())) {
                nowEllipse = &_ellipse[i];
                isInEllipse = 1;
                isInPolygon = 0;
                isInRect = 0;
                isArrow = 0;
                for (int j = 0; j < _fill.length(); j++) {
                    if (_ellipse.at(i).contains(_fill.at(j))) {
                        nowFill = &_fill[j];
                        isInFill = 1;
                    }
                }
//                qDebug()<<"now in ellipse["<<i<<"]";
            }
        }
    }
    if (_polygon.length() > 0) {
        for (int i = 0; i < _polygon.length(); i++) {
            if (polyContains(_polygon[i], e->pos())) {
                nowPolygon = &_polygon[i];
                isInPolygon = 1;
                isInEllipse = 0;
                isInRect = 0;
                isArrow = 0;
                for (int j = 0; j < _fill.length(); j++) {
                    if (polyContains(_polygon[i], _fill.at(j))) {
                        nowFill = &_fill[j];
                        isInFill = 1;
                    }
                }
//                qDebug()<<"now in polygon["<<i<<"]";
            }
        }
    }
    if (!_bezierCurve.empty()) {
        for (int i = 0; i < _bezierCurve.size(); ++i) {
            for (int j = 0; j < _bezierCurve[i].size(); ++j) {
                // 判断当前点是否在控制点的圆内
                // if (e->pos().x() == _bezierCurve[i][j].x() && e->pos().y() == _bezierCurve[i][j].y())
                if (e->pos().x() <= _bezierCurve[i][j].x() + 4 && e->pos().x() >= _bezierCurve[i][j].x() - 4 &&
                    e->pos().y() <= _bezierCurve[i][j].y() + 4 && e->pos().y() >= _bezierCurve[i][j].y() - 4) {
                    isOnPoint1 = 1;
                    isOnPoint2 = 0;
                    isInEllipse = 0;
                    isInPolygon = 0;
                    isInRect = 0;
                    isArrow = 0;
                }
            }
        }
    }
    if (!_bsplineCurve.empty()) {
        for (int i = 0; i < _bsplineCurve.size(); ++i) {
            for (int j = 0; j < _bsplineCurve[i].size(); ++j) {
                // 判断当前点是否在控制点的圆内
                // if (e->pos().x() == _bezierCurve[i][j].x() && e->pos().y() == _bezierCurve[i][j].y())
                if (e->pos().x() <= _bsplineCurve[i][j].x() + 4 && e->pos().x() >= _bsplineCurve[i][j].x() - 4 &&
                    e->pos().y() <= _bsplineCurve[i][j].y() + 4 && e->pos().y() >= _bsplineCurve[i][j].y() - 4) {
                    isOnPoint1 = 0;
                    isOnPoint2 = 1;
                    isInEllipse = 0;
                    isInPolygon = 0;
                    isInRect = 0;
                    isArrow = 0;
                }
            }
        }
    }

    if (transRectTag->contains(e->pos())) {
        isInTagRect = true;
        isArrow = 0;
    }

    if (_drawType == 10) {
        if (isInRect) {
            transMatrix trM;
            trM.setMoveTrans(nowRect->bottomRight() - transRectTag->center());
            transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
            transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
        } else if (isInPolygon) {
            transMatrix trM;
            trM.setMoveTrans((*nowPolygon)[0] - transRectTag->center());
            transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
            transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
        } else if (isInEllipse) {
            transMatrix trM;
            trM.setMoveTrans(nowEllipse->bottomRight() - transRectTag->center());
            transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
            transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
        }

    }


    if (!isArrow && _drag && _drawType == 10) {
        setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
        if (_lpress)
            Transform(e);
    } else {
        setCursor(Qt::ArrowCursor);//恢复原始光标形状
        //_drag = 0;
    }
//    qDebug()<<"pressed:"<<_lpress;

    if (_lpress) {
        qDebug() << "isInEllipse" << isInEllipse;
        qDebug() << "isInPolygon" << isInPolygon;
        qDebug() << "isInRect" << isInRect;
        qDebug() << "[move] _drawtype:" << _drawType;
        if (_drawType == 1)//铅笔画线
        {
            if (_lines.size() <= 0) return;//线条集合为空，不画线
            QVector<QPoint> &lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
            update();//触发窗体重绘
        } else if (_drawType == 2) {
//            qDebug()<<"drag:"<<_drag;
            QRect & lastRect = _rects.last();//拿到新矩形
            lastRect.setBottomRight(e->pos());

            update();//触发窗体重绘

        } else if (_drawType == 3) {
            if (_drag == 0)//非拖拽
            {
                QRect & lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setBottomRight(e->pos());//更新椭圆的右下角坐标
            }
            update();//触发窗体重绘
        } else if (_drawType == 4 && _line.length() > 0) {
            QRect & lastLine = _line.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            qDebug() << "update line";
            update();//触发窗体重绘
        } else if (_drawType == 5 && _arc.length() > 0) {

            QRect & lastArc = _arc.last();//拿到新圆弧
            lastArc.setBottomRight(e->pos());//更新圆弧的右下角坐标)
            update();//触发窗体重绘
        } else if (_drawType == 6) {
            update();//触发窗体重绘
        } else if (_drawType == 7) {
            qDebug() << "not in polygon";
            update();//触发窗体重绘
        } else if (_drawType == 10) { // bezier/spline移动控制点
            if (!_bezierCurve.empty() && isOnPoint1 && !isOnPoint2 && !isInEllipse && !isInPolygon && !isInRect) {
                *nowControlPoint = QPoint(e->pos().x(), e->pos().y());
                _begin = e->pos();//刷新拖拽点起始坐标
            }
            isOnPoint1 = 0;
            if (!_bsplineCurve.empty() && !isOnPoint1 && isOnPoint2 && !isInEllipse && !isInPolygon && !isInRect) {
                *nowControlPoint = QPoint(e->pos().x(), e->pos().y());
                _begin = e->pos();//刷新拖拽点起始坐标
            }
            isOnPoint2 = 0;
            update();
        } else if (_drawType == 12) {
            _crop.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
    }
}


void MyPaint::mouseReleaseEvent(QMouseEvent *e) {
    if (_lpress) {
        if (_drawType == 1) {
            QVector<QPoint> &lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录线条的结束坐标
            _lpress = false;//标志左键释放
        } else if (_drawType == 2) {
            QRect & lastRect = _rects.last();//拿到新矩形
            if (!_drag) {
                lastRect.setBottomRight(e->pos());//不是拖拽时，更新矩形的右下角坐标)
            }

            _lpress = false;

        } else if (_drawType == 3) {
            QRect & lastEllipse = _ellipse.last();//拿到新椭圆
            if (!_drag) {
                lastEllipse.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
            }
            _lpress = false;
            update();
        } else if (_drawType == 4) {
            QRect & lastLine = _line.last();//拿到新直线
            if (!_drag) {
                lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            }
            _lpress = false;
        } else if (_drawType == 5) {
            cout << "closing secCircle" << endl;
            QRect & last = _arc.last();//拿到新圆弧
            last.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
            _lpress = false;
        } else if (_drawType == 6) {
            _arcCenter.pop_back();
            _lpress = false;
        } else if (_drawType == 7) {
            //多边形创建过程中会多次松开
//            _lpress = false;//标志左键释放
            update();
        } else if (_drawType == 8) {
            // 多边形窗口的裁切
            _lpress = false;
            update();
        } else if (_drawType == 9) {
            _lpress = false;
            update();
        } else if (_drawType == 13) {
            _lpress = false;
            update();
        } else if (_drawType == 10) {
            _lpress = false;
            iscomfirm = true;
        } else if (_drawType == 11) {
            _lpress = false;
            update();
        } else if (_drawType == 12) {
            _lpress = false;
            int XL = _crop.topLeft().x() < _crop.bottomRight().x() ? _crop.topLeft().x() : _crop.bottomRight().x();
            int XR = _crop.topLeft().x() > _crop.bottomRight().x() ? _crop.topLeft().x() : _crop.bottomRight().x();
            int YB = _crop.topLeft().y() > _crop.bottomRight().y() ? _crop.topLeft().y() : _crop.bottomRight().y();
            int YT = _crop.topLeft().y() < _crop.bottomRight().y() ? _crop.topLeft().y() : _crop.bottomRight().y();
            QVector<QRect> newLine;
            QVector<QPen> newBrush;
            vector<int> deleteNo;
            int k = 0;
            for (int i = 0; i < _shape.length(); i++) {
                if (_shape.at(i) == 4) {
                    QPen pen = _brush.at(i);
                    QRect line = _line.at(k++);
                    QRect newline = MidPoint_ClipLine(line, XL, XR, YB, YT);
                    if (newline.topLeft().x() != -1) {//如果不是完全剪切整条线段
                        newLine.append(newline);
                        newBrush.append(pen);
                    }
                    deleteNo.push_back(i);
                }
            }
            sort(deleteNo.rbegin(), deleteNo.rend());
            for (int i = 0; i < deleteNo.size(); ++i) {
                _line.remove(deleteNo.size() - i - 1);
                _shape.remove(deleteNo[i]);
                _brush.remove(deleteNo[i]);
            }
            for (int i = 0; i < _shape.length(); i++) {
                if (_shape.at(i) == 12) {
                    _shape.remove(i);
                    _brush.remove(i);
                }
            }
            for (int i = 0; i < newLine.length(); ++i) {
                _line.append(newLine.at(i));
                _brush.append(newBrush.at(i));
                _shape.append(4);
                update();
            }
        }
    }
}

void MyPaint::Lines() {
    _drawType = 1;//铅笔
    _drag = 0;
}

void MyPaint::Line() {
    _drawType = 4;//直线
    _drag = 0;
}

void MyPaint::Rects() {
    _drawType = 2;//矩形
    _drag = 0;

}

void MyPaint::Ellipses() {
    _drawType = 3;//椭圆
    _drag = 0;
}

void MyPaint::Arc() {
    _drawType = 5;//圆弧
    _drag = 0;
}


void MyPaint::ArcCenter() {
    _drawType = 6;//圆弧圆心
    _drag = 0;
}

void MyPaint::Polygon() {
    _drawType = 7;
    _drag = 0;
}

void MyPaint::ClipPolygon() {
    _drawType = 8; // 裁切多边形
    _drag = 0;
}

void MyPaint::Bezier() {
    _drawType = 9;
    _drag = 0;
}

void MyPaint::Bspline() {
    _drawType = 13;
    _drag = 0;
}

void MyPaint::startTrans() {
    if (_shape.length() != 0) {
        _drawType = 10;
        _drag = 0;
    }
}

void MyPaint::startFill() {
    _drawType = 11;
    _drag = 0;
}

void MyPaint::Clip() {
    _drawType = 12;
    _drag = 0;
}


void MyPaint::SavePic() {
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0) {
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(0, 30, size().width(), size().height() - 30)).save(fileName);//不包含工具栏
    }
}

void MyPaint::OpenPic() {
    //弹出文件打开对话框
    QString picPath = QFileDialog::getOpenFileName(this, tr("打开"), "", "Image Files(*.jpg *.png)");
    if (!picPath.isEmpty())//用户选择了文件
    {
        QPixmap pix;
        pix.load(picPath);//加载图片
        QPainter p(&_pixmap);
        p.drawPixmap(0, 30, pix);//添加工具栏的空间
        _openflag = 1;//设置文件打开标志
        update();//触发窗体重绘，将图片画到窗体
    }
}



void MyPaint::createBrushWindow() {
    emit sendPen(&_pen);
    setBrushWindow->show();
}

void MyPaint::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    _Rmenu->exec(cursor().pos());//在光标位置弹出菜单
}

void MyPaint::keyReleaseEvent(QKeyEvent *e){
    state = IDLE;
}

void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
    QPoint coinPos = _stage->getCoinPos();
    if (hasCollision(QPoint(playerX,playerY), coinPos)) {
        _playerStatus = WIN;
        showMessageBox();
        qDebug() << "collision";
    }
    if(e->key() == Qt::Key_Space){
        if (!canDrop(playerX, playerY))
            jumpCount = 0;
        if (jumpCount < 3)
        {
            jumpCount++;
            playerY-=40;
            state = JUMP;
            update();
        }

    }
    if(e->key() == Qt::Key_D){
        if(playerX>=582){
            return;
        }
        if(canWalkRight(playerX,playerY)){//走平地
            playerX+=5;
            state = RUN_R;
        }else{
            //磕到脚了，接下来看看能不能跨步往上走
            if(noRightWall(playerX,playerY)){
                playerX+=5;
                playerY-=4;
                state = RUN_R;
            }

        }

        update();
//        qDebug()<<"pressed D";
    }
    if(e->key() == Qt::Key_A){
        if(playerX<=5){
            return;
        }
        if(canWalkLeft(playerX,playerY)){
            playerX-=5;
            state = RUN_L;
        }else{
            //磕到脚了，接下来看看能不能跨步往上走
            if(noLeftWall(playerX,playerY)){
                playerX-=5;
                playerY-=4;
                state = RUN_L;
            }

        }

        update();
//        qDebug()<<"pressed D";
    }

    //Ctrl+Z撤销
    if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier) {
        if (_shape.size() > 0) {
            switch (_shape.last()) {
                case 1:
                    _lines.pop_back();
                    break;
                case 2:
                    _rects.pop_back();
                    break;
                case 3:
                    _ellipse.pop_back();
                    break;
                case 4:
                    _line.pop_back();
                    break;
                case 5:
                    _arc.pop_back();
                    break;
                case 6:
                    _arcCenter.pop_back();
                    break;
            }
            _shape.pop_back();
            _drag = 0;//设置为非拖拽模式
            update();
        }
    } else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
    {
        SavePic();//Ctrl+S保存
    } else if (e->key() == Qt::Key_Escape){
        if (_drawType == 7) {
            update();
            _lpress = false;
            _newPolygon = true;
        }
        if (_drawType == 9) { // bezier控制点绘制结束
            _brush.append(_pen);
            _shape.append(9);
            _bezierCurve.push_back(_currentBezierCurve);
            vector<QPoint>().swap(_currentBezierCurve);
            update();
        }
        if (_drawType == 13) { // bspline控制点绘制结束
            _brush.append(_pen);
            _shape.append(13);
            _bsplineCurve.push_back(_currentBsplineCurve);
            vector<QPoint>().swap(_currentBsplineCurve);
            update();
        }
        if (_drawType == 8) { // 裁切多边形绘制结束
            update();
            QVector<QVector<QPoint>> newPolygon;
            QVector<QPen> newBrush;
            vector<int> deleteIndex;
            int k = 0;
            for (int i = 0; i < _shape.length(); i++) {
                if (_shape.at(i) == 7) {
                    QPen pen = _brush.at(i);
                    QVector<QPoint> polygon = cropPolygon(_polygon.at(k++), _cropPolygon);
                    if (polygon.length() >= 3) {
                        // 如果返回的多边形的长度大于等于3，则说明裁切后的多边形不为空，将他们追加到新的多边形数组中
                        newPolygon.append(polygon);
                        newBrush.append(pen);
                    }
                    deleteIndex.push_back(i);
                }
            }
            sort(deleteIndex.rbegin(), deleteIndex.rend());
            for (int i = 0; i < deleteIndex.size(); ++i) {
                _polygon.remove(deleteIndex.size() - i - 1);
                _shape.remove(deleteIndex[i]);
                _brush.remove(deleteIndex[i]);
            }
            // 找到裁切多边形，并删除它
            for (int i = 0; i < _shape.length(); i++) {
                if (_shape.at(i) == 8) {
                    _shape.remove(i);
                    _brush.remove(i);
                }
            }
            _cropPolygon.clear();
            for (int i = 0; i < newPolygon.length(); ++i) {
                _polygon.append(newPolygon.at(i));
                _brush.append(newBrush.at(i));
                _shape.append(7);
                update();
            }
        }
    } else if (e->key() == Qt::Key_M && _drawType == 10) {

        _transFlag = MOVE;
    } else if (e->key() == Qt::Key_Z && _drawType == 10) {
        _transFlag = ZOOM;
    } else if (e->key() == Qt::Key_R && _drawType == 10) {
        _transFlag = ROTATE;
    } else if (e->key() == Qt::Key_S && _drawType == 10) {
        isSpecificRefer = false;
        update();
    }
}

/**变换函数**/
void MyPaint::Transform(QMouseEvent *e) {
    if (isInRect)
        rectTrans(e);
    else if (isInEllipse)
        circleTrans(e);
    else if (isInPolygon)
        polygonTrans(e);
}

void MyPaint::rectTrans(QMouseEvent *e) {   //对矩形做变换
    transMatrix trM;
    double zoomPropor_X, zoomPropor_Y;  //进行缩放的比例
    QPoint moveVector;              //进行移动的向量
    double angle;

    if (iscomfirm) {
        tempTransRect = *nowRect;
        iscomfirm = false;
    }
    if (isSpecificRefer) {
        trM.setReference(referancePoint);  //是否有用户设定的参考点，有则设为该点
    } else {
        referancePoint = nowRect->center();
        trM.setReference(referancePoint);   //没有则设为矩形中心
    }
    switch (_transFlag) {
        /*case MOVE:
            int dx = e->pos().x()-_begin.x();//横向移动x
            int dy = e->pos().y()-_begin.y();//纵向移动y
            qDebug()<<"x "<<_begin.x()<<" ,"<<"y "<<_begin.y();
            *nowRect = (*nowRect).adjusted(dx,dy,dx,dy);
            _begin = e->pos();//刷新拖拽点起始坐标
            update();
            break;*/
        case MOVE:
            qDebug() << "isinMove";
            moveVector = e->pos() - _begin;    //计算移动向量，终点减起点
            trM.setMoveTrans(moveVector);
            nowRect->setTopLeft(trM * nowRect->topLeft());
            nowRect->setBottomRight(trM * nowRect->bottomRight());
            if (isInFill) {
                trM.setMoveTrans(nowRect->center() - *nowFill);
                (*nowFill) = trM * (*nowFill);
            }
            _begin = e->pos();
            update();

            break;
        case ZOOM:
            if (isInTagRect) {
                //计算缩放比例，直接来说就是计算怎么让标志矩形中心点移动到现在的点
                zoomPropor_X = abs(e->pos().x() - referancePoint.x()) * 1.0 /
                               abs(tempTransRect.bottomRight().x() - referancePoint.x());
                zoomPropor_Y = abs(e->pos().y() - referancePoint.y()) * 1.0 /
                               abs(tempTransRect.bottomRight().y() - referancePoint.y());
                trM.setZoomTrans(zoomPropor_X, zoomPropor_Y); //生成缩放变换矩阵
                nowRect->setTopLeft(trM * tempTransRect.topLeft());
                nowRect->setBottomRight(trM * tempTransRect.bottomRight());  //对目标矩形的两个点同步变换
                if (isInFill) {
                    trM.setMoveTrans(nowRect->center() - *nowFill);
                    (*nowFill) = trM * (*nowFill);
                }
                trM.setMoveTrans(nowRect->bottomRight() - transRectTag->center()); //让标志矩形中心点跟随移动到新点
                transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
                transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
            }
            _begin = e->pos();
            update();
            break;
        case ROTATE:
            if (isInTagRect) {
                QPen tempPen(_pen);

            }


    }
}

void MyPaint::polygonTrans(QMouseEvent *e) {
    transMatrix trM;
    double zoomPropor_X, zoomPropor_Y;  //进行缩放的比例
    QPoint moveVector;              //进行移动的向量
    double angle;

    if (iscomfirm) {
        tempTransPoly = *nowPolygon;
        iscomfirm = false;
    }

    if (isSpecificRefer)
        trM.setReference(referancePoint);
    else {
        referancePoint = getPolyCenter(*nowPolygon);
        trM.setReference(referancePoint);
    }

    switch (_transFlag) {
        case MOVE:
            moveVector = e->pos() - _begin;    //计算移动向量，终点减起点
            trM.setMoveTrans(moveVector);
            for (int i = 0; i < nowPolygon->size(); ++i) {
                (*nowPolygon)[i] = trM * ((*nowPolygon)[i]);
            }
            if (isInFill) {
                trM.setMoveTrans(getPolyCenter(*nowPolygon) - *nowFill);
                (*nowFill) = trM * (*nowFill);
            }
            _begin = e->pos();
            update();
            break;
        case ZOOM:
            if (isInTagRect) {
                //zoomPropor_X = abs(e->pos().x() - referancePoint.x())*1.0/abs(_begin.x() - referancePoint.x());
                //zoomPropor_Y = abs(e->pos().y() - referancePoint.y())*1.0/abs(_begin.y() - referancePoint.y());
                zoomPropor_X =
                        abs(e->pos().x() - referancePoint.x()) * 1.0 / abs(tempTransPoly[0].x() - referancePoint.x());
                zoomPropor_Y =
                        abs(e->pos().y() - referancePoint.y()) * 1.0 / abs(tempTransPoly[0].y() - referancePoint.y());
                trM.setZoomTrans(zoomPropor_X, zoomPropor_Y); //生成缩放变换矩阵
                for (int i = 0; i < nowPolygon->size(); ++i) {
                    (*nowPolygon)[i] = trM * tempTransPoly[i];
                }
                if (isInFill) {
                    trM.setMoveTrans(getPolyCenter(*nowPolygon) - *nowFill);
                    (*nowFill) = trM * (*nowFill);
                }
                trM.setMoveTrans((*nowPolygon)[0] - transRectTag->center()); //让标志矩形中心点跟随移动到新点
                transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
                transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
                update();
                //_begin = e->pos();
            }
            break;
        case ROTATE:
            if (isInTagRect) {
                angle = getAngle(referancePoint, tempTransPoly[0], e->pos());
                trM.setRotateTrans(angle);
                if (angle > 30 || angle < -30)   /**旋转时连续旋转超过60多度时会出现bug，目前原因尚不明确，处理方法为每次超过30度时更新暂存多边形，则下次的角度从零计算**/
                    iscomfirm = true;     /**切勿删除！！！！！！！！！！！！**/
                for (int i = 0; i < nowPolygon->size(); ++i) {
                    (*nowPolygon)[i] = trM * tempTransPoly[i];
                }
                if (isInFill) {
                    trM.setMoveTrans(getPolyCenter(*nowPolygon) - *nowFill);
                    (*nowFill) = trM * (*nowFill);
                }
                trM.setMoveTrans((*nowPolygon)[0] - transRectTag->center()); //让标志矩形中心点跟随移动到新点
                transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
                transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
                _begin = e->pos();
                update();
            }
    }

}

void MyPaint::circleTrans(QMouseEvent *e) {
    transMatrix trM;
    double zoomPropor_X, zoomPropor_Y;  //进行缩放的比例
    QPoint moveVector;              //进行移动的向量
    double angle;
    int R;
    if (iscomfirm) {
        tempTransRect = *nowEllipse;
        iscomfirm = false;
    }
    if (isSpecificRefer) {
        trM.setReference(referancePoint);  //是否有用户设定的参考点，有则设为该点
    } else {
        referancePoint = nowEllipse->center();
        trM.setReference(referancePoint);   //没有则设为矩形中心
    }
    switch (_transFlag) {

        case MOVE:
            moveVector = e->pos() - _begin;    //计算移动向量，终点减起点
            trM.setMoveTrans(moveVector);
            nowEllipse->setTopLeft(trM * nowEllipse->topLeft());
            nowEllipse->setBottomRight(trM * nowEllipse->bottomRight());
            if (isInFill) {
                trM.setMoveTrans(nowEllipse->center() - *nowFill);
                (*nowFill) = trM * (*nowFill);
            }
            _begin = e->pos();
            update();
        case ZOOM:
            if (isInTagRect) {
                //计算缩放比例，直接来说就是计算怎么让标志矩形中心点移动到现在的点
                zoomPropor_X = abs(e->pos().x() - referancePoint.x()) * 1.0 /
                               abs(tempTransRect.bottomRight().x() - referancePoint.x());
                trM.setZoomTrans(zoomPropor_X, zoomPropor_X); //生成缩放变换矩阵
                nowEllipse->setTopLeft(trM * tempTransRect.topLeft());
                nowEllipse->setBottomRight(trM * tempTransRect.bottomRight());  //对目标圆外接矩形的两个点同步变换
                if (isInFill) {
                    trM.setMoveTrans(nowRect->center() - *nowFill);
                    (*nowFill) = trM * (*nowFill);
                }
                trM.setMoveTrans(nowEllipse->bottomRight() - transRectTag->center()); //让标志矩形中心点跟随移动到新点
                transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
                transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
            }
            _begin = e->pos();
            update();
            break;
        case ROTATE:
            if (isInTagRect) {
                angle = getAngle(referancePoint, tempTransRect.bottomRight(), e->pos());
                trM.setRotateTrans(angle);
                if (angle > 30 || angle < -30)   /**旋转时连续旋转超过60多度时会出现bug，目前原因尚不明确，处理方法为每次超过30度时更新暂存多边形，则下次的角度从零计算**/
                    iscomfirm = true;     /**切勿删除！！！！！！！！！！！！**/

                R = tempTransRect.width();
                nowEllipse->setBottomRight(trM * tempTransRect.bottomRight());
                nowEllipse->setTopLeft(QPoint(nowEllipse->bottomRight().x() - R, nowEllipse->bottomRight().y() + R));

                if (isInFill) {
                    trM.setMoveTrans(nowEllipse->center() - *nowFill);
                    (*nowFill) = trM * (*nowFill);
                }
                trM.setMoveTrans(nowEllipse->bottomRight() - transRectTag->center()); //让标志矩形中心点跟随移动到新点
                transRectTag->setTopLeft(trM * (transRectTag->topLeft()));
                transRectTag->setBottomRight(trM * (transRectTag->bottomRight()));
                _begin = e->pos();
                update();
            }
            break;
    }

}

void MyPaint::showMessageBox() {
    QMessageBox msgBox;
    if (_playerStatus == WIN) {
        msgBox.setText("You Win!!!");
    } else if (_playerStatus == DIE) {
        msgBox.setText("Game Over!!!");
    }
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close);
    int choice = msgBox.exec();
    switch (choice) {
        case QMessageBox::Reset:
            cleanScreen();
            break;
        case QMessageBox::Close:
            close();
            break;
        default:
            // should never be reached
            break;
    }
}




