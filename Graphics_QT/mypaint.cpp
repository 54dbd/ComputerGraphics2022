#include "mypaint.h"
#include "Line.h"
#include "Circle.h"
#include "Arc.h"
#include "Polygon.h"
#include "Bezier.h"
#include "Fill.h"
#include <QDebug>
#include <iostream>
#include <QRect>
#include "newwindow.h"
using namespace std;
vector<vector<pointData>> MAP;
MyPaint::MyPaint(QWidget *parent) :
    QMainWindow(parent)
{
     _lpress = false;//初始鼠标左键未按下
     _newPolygon = true;//代表多边形可以新建
     _drag = 0;//默认非拖拽模式
     _drawType = 0;//初始为什么都不画
     _begin = pos();//拖拽的参考坐标，方便计算位移
     _openflag = 0;//初始不打开图片

     this->setGeometry(350,200,600,400);//设置窗体大小、位置，大小：(600*400)px
     setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
     //设置背景白色
       this->setStyleSheet("background-color:white;");
     //初始化MAP
     for(int i=0;i<600;i++){
         vector<pointData> row;
         MAP.push_back(row);
         for(int j=0;j<400;j++){
             //对每一行中的每一列进行添加点
             pointData point(QPoint(i,j), Qt::white);
             MAP[i].push_back(point);
         }
     }

    //创建工具栏
    QToolBar *tbar = addToolBar(tr("工具栏"));
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

    QAction *moveAction = new QAction(tr("&移动"), this);//移动
    tbar->addAction(moveAction);//添加到工具栏

    QAction *fillAction = new QAction(tr("&填充"), this);//填充
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
    polygonAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
    tbar->addAction(polygonAction);

    QAction *bezierAction = new QAction(tr("&贝塞尔"), this);//贝塞尔
    tbar->addAction(bezierAction);





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

    connect(setBrush, SIGNAL(triggered()),this,SLOT(createBrushWindow()));
    connect(moveAction,SIGNAL(triggered()),this,SLOT(startMove()));
    connect(fillAction,SIGNAL(triggered()),this,SLOT(startFill()));

    //设置界面传参
    connect(this,SIGNAL(sendPen(QPen*)),setBrushWindow,SLOT(getPen(QPen*)));
}

void MyPaint::paintEvent(QPaintEvent *)
{
    if(_openflag == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        _pixmap = QPixmap(size());//新建pixmap
        _pixmap.fill(Qt::white);//背景色填充为白色
    }
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    //QPainter p=_pen;//将_pixmap作为画布
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0, i9 = 0, i11=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        // 获取对应的笔刷颜色，并设置
        QPen pen = _brush.at(c);
        p.setPen(pen);
        if(_shape.at(c) == 1)//线条
        {
              const QVector<QPoint>& line = _lines.at(i1++);//取出一条线条
              for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
              {
                  int x_s = line.at(j).x();
                  int x_e = line.at(j+1).x();
                  int y_s = line.at(j).y();
                  int y_e = line.at(j+1).y();
                  class Line l(x_s,y_s,x_e,y_e,1,p, pen);
                  l.MidPoint();
              }
        }
        else if(_shape.at(c) == 2)//矩形
        {
            QPoint start,end;
            start = _rects.at(i2).topLeft();
            end = _rects.at(i2).bottomRight();
            int x_s = start.x();
            int x_e = end.x();
            int y_s = start.y();
            int y_e = end.y();
            //创建直线
            class Line l1(x_s,y_s,x_e,y_s,1,p, pen);
            class Line l2(x_s,y_s,x_s,y_e,1,p, pen);
            class Line l3(x_e,y_e,x_s,y_e,1,p, pen);
            class Line l4(x_e,y_e,x_e,y_s,1,p, pen);
            if(!_lpress){//松开时
                l1.MidPoint();
                l2.MidPoint();
                l3.MidPoint();
                l4.MidPoint();
            }else{//按住时
                l1.MidPointNoMap();
                l2.MidPointNoMap();
                l3.MidPointNoMap();
                l4.MidPointNoMap();
            }



            i2++;
        }
        else if(_shape.at(c) == 3)//正圆
        {
            QPoint center;
            center = _ellipse.at(i3).center();
            int R = abs(center.y() - _ellipse.at(i3).bottom());

            //画圆
            Circle C(center.x(),center.y(),0,1,p, pen);
            C.SetR(R);
            C.DrawCircle();
            i3++;
        }
        else if(_shape.at(c) == 4)//直线
        {
            QPoint start,end;
            start = _line.at(i4).topLeft();
            end = _line.at(i4).bottomRight();
            int x_s = start.x();
            int x_e = end.x();
            int y_s = start.y();
            int y_e = end.y();
            //创建直线
            class Line l(x_s,y_s,x_e,y_e,1,p, pen);
            l.MidPoint();
            i4++;

        }
        else if(_shape.at(c) == 5)
        {

            //画圆弧
            //_secCircle=0;
            QPoint start,end;
            struct arcCenter center;
            start = _arc.at(i5).topLeft();
            end = _arc.at(i5).bottomRight();
            int x_s = start.x();
            int y_s = start.y();


            center = _arcCenter.at(i5);
            center.R = sqrt((x_s-center.x)*(x_s-center.x)+(y_s-center.y)*(y_s-center.y));
            //圆弧圆心

            //使圆心不受笔刷大小影响
            QPen temp = pen;
            pen.setWidth(1);
            p.setPen(pen);

            Brush b(3,p,pen);
            if(i5==_arcCenter.length()-1)//只保留最后一个
                b.drawPixel(center.x,center.y);

            //恢复笔刷大小
            pen = temp;
            p.setPen(pen);

            class Arc a(center.x,center.y,center.R, 1, p, pen);
            a.DrawArc(start.x(),start.y(),end.x(),end.y());

            i5++;



        }
        else if(_shape.at(c) == 6){

        }
        else if (_shape.at(c) == 7) { // 绘制多边形
            const QVector<QPoint>& polygon = _polygon.at(i7++);//取出一个多边形
            class Polygon poly(1, p, this->screen()->size().height(), pen);
            for(int j = 0; j < polygon.size(); ++j)//将多边形的所有线段描绘出
            {
                int temp = (j + 1) % polygon.size();
                int x_s = polygon.at(j).x();
                int x_e = polygon.at(temp).x();
                int y_s = polygon.at(j).y();
                int y_e = polygon.at(temp).y();
                Edge *e = new Edge(x_s, y_s, x_e, y_e);
                poly.addEdgeToET(e);
            }
            poly.drawPolygon();
        }
        else if(_shape.at(c) == 8){


        }
        else if (_shape.at(c) == 9){ // bezier
            const vector<point2d>& bezierCurve = _bezierCurve.at(i9++);

            // 画控制点
            for (auto i : bezierCurve) {
                Circle C(i.x,i.y,4,1,p, pen);
                C.DrawCircle();
            }
            class Bezier b(1, p, bezierCurve, pen);
            b.drawBezier();
        }
        else if(_shape.at(c) == 11){//fill
            class Fill f(pix,p,pen);
//            f.fillColor(Qt::blue);
            //f.fillRect(*nowRect);
            //DEBUG: test rect for all the shape
            //
//            QPoint p;
            qDebug()<<"[paintEvent]filling i11[ "<<i11<<" ]";
            f.getColorMap();
            f.fillShape(_fill.at(i11),pen.color());
            i11++;
//            f.restoreColor();
//            if(isInRect){
//                //f.fillRect(*nowRect);
//                //f.restoreColor();
//            }else if (isInEllipse){

//            }else if(isInPolygon){

//            }

        }

    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent *e)
{

    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        qDebug()<<"_brushSize:"<<_brush.length();
        qDebug()<<"_shapeSize:"<<_shape.length();

        _drag = 0;
        QPen tempPen(_pen);
        if(_drawType == 10){//移动
            _drag = 1;
            qDebug()<<"drag:"<<_drag;

        }
        if (_drawType == 7)//多边形处理笔刷
        {
            qDebug()<<"drawing polygon";
            tempPen.setWidth(1);
        }
        // 防止Bezier或者移动操作 每新建一个点，就会添加一个笔刷，造成笔刷数组中存在大量的多余笔刷，导致修改颜色失效
        else if(_drawType == 0 || _drawType == 9 || _drawType == 10) { // Bezier & move
            qDebug()<<"drawing bezier";
            qDebug()<<"moving shape";
        }
        else{
            _brush.append(tempPen);//将当前笔刷颜色加入到笔刷颜色列表中

        }

        if(_drawType == 1)//线条(铅笔)
        {
            _lpress = true;//左键按下标志
            QVector<QPoint> line;//鼠标按下，新的线条开始
            _lines.append(line);//将新线条添加到线条集合
            QVector<QPoint>& lastLine = _lines.last();//拿到新线条
            lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
            _shape.append(1);
        }
        else if(_drawType == 2||(_drawType == 10&& isInRect))//矩形
        {
            _lpress = true;//左键按下标志

            if(!_drag){
                qDebug()<<"new rect";
                QRect rect;//鼠标按下，矩形开始
                _rects.append(rect);//将新矩形添加到矩形集合
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setTopLeft(e->pos());//记录鼠标的坐标(新矩形的左上角坐标)
                 _shape.append(2);
            }else{
                //寻找当前是哪个图形
                if(isInRect){
                    _begin = e->pos();
                    qDebug()<<"found the rect";
                }
            }
        }
        else if(_drawType == 3||(_drawType == 10&& isInEllipse))//椭圆
        {
            _lpress = true;//左键按下标志

            if(!_drag){
                QRect rect;//鼠标按下，椭圆开始
                qDebug()<<"new ellipse";
                _ellipse.append(rect);//将新椭圆添加到椭圆集合
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                 _shape.append(3);
            }else{
                qDebug()<<"isInEllipse"<<isInEllipse;
                if(isInEllipse){
                    _begin = e->pos();
                    qDebug()<<"found the ellipse";

                }
            }


        }
        else if(_drawType == 4)//直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(4);
        }
        else if(_drawType == 5)//圆弧
        {
            if(_arcCenter.length()==0)
                return;
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，正圆开始

            qDebug("_arc.appending...");
            _arc.append(rect);//将新正圆添加到椭圆集合
            QRect& lastArc = _arc.last();//拿到新圆弧
            lastArc.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
            if(_arcCenter.length()<_arc.length()){//如果出现了在一个圆心上重复画弧的情况，就复制一个最后一个圆弧心
                struct arcCenter center;
                center.x=_arcCenter.last().x;
                center.y=_arcCenter.last().y;
                _arcCenter.append(center);
            }

            _shape.append(5);
        }
        else if(_drawType == 6){//圆弧圆心
            struct arcCenter center;
            center.x=e->pos().x();
            center.y=e->pos().y();
            _arcCenter.append(center);
            qDebug()<<"center at"<<center.x<<","<<center.y;
        }
        else if (_drawType == 7||(_drawType == 10&& isInPolygon)) { // 绘制多边形
            _lpress = true;//左键按下标志
            if(!_drag){
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
                QVector<QPoint>& lastPolygon = _polygon.last();
                // 创建点
                QPoint a;
                a.setX(e->pos().x());
                a.setY(e->pos().y());
                qDebug() << "x:" << a.x() << "y:" << a.y();
                // 将新的点添加到多边形集合
                lastPolygon.append(a);
            }else{
                qDebug()<<"isInPolygon"<<isInPolygon;
                if(isInPolygon){
                    _begin = e->pos();
                    qDebug()<<"found the polygon";
                }
            }
        }
        else if(_drawType == 8){


        }
        else if (_drawType == 9){// beizer
            _lpress = true;
            point2d p(e->pos().x(), e->pos().y());
            _currentBezierCurve.push_back(p);
            qDebug() << "x:" << e->pos().x() << "y:" << e->pos().y();
        }
        else if(_drawType == 11){//fill
            _lpress = true;
            QPoint pos = e->pos();
            _fill.append(pos);
            qDebug()<<"start fill at"<<pos.x()<<", "<<pos.y();
            _shape.append(11);
        }


    }
}



void MyPaint::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<< "current color:"<<MAP[e->pos().x()][e->pos().y()].getColor();
    isInRect = 0;
    isInEllipse = 0;
    isInPolygon = 0;
    int isArrow = 1;
    //定位鼠标指到的图形
    if(_rects.length()>0 ){
        for(int i=0;i<_rects.length();i++ ){
            if(_rects.at(i).contains(e->pos()))
            {
                nowRect = &_rects[i];
                isInRect = 1;
                isArrow = 0;
//                qDebug()<<"now in rect["<<i<<"]";
            }
        }
    }
    if(_ellipse.length()>0){
        for(int i=0;i<_ellipse.length();i++ ){
            if(_ellipse.at(i).contains(e->pos()))
            {
                nowEllipse =&_ellipse[i];
                isInEllipse = 1;
                isArrow = 0;
//                qDebug()<<"now in ellipse["<<i<<"]";
            }
        }
    }
    if(_polygon.length()>0){
        for(int i=0;i<_polygon.length();i++ ){
            if(polyContains(_polygon[i],e->pos()))
            {
                nowPolygon =&_polygon[i];
                isInPolygon = 1;
                isArrow = 0;
//                qDebug()<<"now in polygon["<<i<<"]";
            }
        }
    }

    if(!isArrow && _drag)
    {
        setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
    }else{
        isInEllipse = 0;
        isInPolygon = 0;
        isInRect = 0;
        setCursor(Qt::ArrowCursor);//恢复原始光标形状
        //_drag = 0;
    }
//    qDebug()<<"pressed:"<<_lpress;

    if(_lpress)
    {
        qDebug()<<"isInEllipse"<<isInEllipse;
        qDebug()<<"isInPolygon"<<isInPolygon;
        qDebug()<<"isInRect"<<isInRect;
        qDebug()<<"[move] _drawtype:"<<_drawType;
        if(_drawType == 1)//铅笔画线
        {
            if(_lines.size()<=0) return;//线条集合为空，不画线
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
            update();//触发窗体重绘
        }
        else if(_drawType == 2||(_drawType==10&&isInRect))
        {
//            qDebug()<<"drag:"<<_drag;
            if(_drag==0)
            {
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setBottomRight(e->pos());
            }else if(isInRect){
                int dx = e->pos().x()-_begin.x();//横向移动x
                int dy = e->pos().y()-_begin.y();//纵向移动y
                qDebug()<<"x "<<_begin.x()<<" ,"<<"y "<<_begin.y();
                *nowRect = (*nowRect).adjusted(dx,dy,dx,dy);
                _begin = e->pos();//刷新拖拽点起始坐标

            }
            update();//触发窗体重绘

        }
        else if(_drawType == 3|| (_drawType==10&&isInEllipse))
        {
            if(_drag == 0)//非拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setBottomRight(e->pos());//更新椭圆的右下角坐标)

            }else if(isInEllipse){
                int dx = e->pos().x()-_begin.x();//横向移动x
                int dy = e->pos().y()-_begin.y();//纵向移动y
                qDebug()<<"x "<<_begin.x()<<" ,"<<"y "<<_begin.y();
                *nowEllipse = (*nowEllipse).adjusted(dx,dy,dx,dy);
                _begin = e->pos();//刷新拖拽点起始坐标

            }
            update();//触发窗体重绘
        }
        else if(_drawType == 4 && _line.length() > 0)
        {
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            qDebug()<<"update line";
            update();//触发窗体重绘
        }
        else if(_drawType == 5 && _arc.length() > 0)
        {
            QRect& lastArc = _arc.last();//拿到新圆弧
            lastArc.setBottomRight(e->pos());//更新圆弧的右下角坐标)
            update();//触发窗体重绘
        }
        else if(_drawType == 6)
        {
            update();//触发窗体重绘
        }
        else if(_drawType == 7||(_drawType==10&&isInPolygon)){
            if(isInPolygon){
                int dx = e->pos().x()-_begin.x();//横向移动x
                int dy = e->pos().y()-_begin.y();//纵向移动y
                qDebug()<<"x "<<_begin.x()<<" ,"<<"y "<<_begin.y();
                for(int i=0;i<(*nowPolygon).length();i++){//让每个点都移动相同x,y
                    (*nowPolygon)[i].setX((*nowPolygon)[i].x()+dx);
                    (*nowPolygon)[i].setY((*nowPolygon)[i].y()+dy);
//                    (*nowPolygon)[i].setX(10);
//                    (*nowPolygon)[i].setY(10);
                }
                _begin = e->pos();//刷新拖拽点起始坐标

            }
            qDebug()<<"not in polygon";
            update();//触发窗体重绘
        }
    }
}


void MyPaint::mouseReleaseEvent(QMouseEvent *e)
{
    if(_lpress)
    {
        if(_drawType == 1)
        {
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录线条的结束坐标
            _lpress = false;//标志左键释放
        }
        else if(_drawType == 2)
        {
            QRect& lastRect = _rects.last();//拿到新矩形
            if(!_drag)
            {
                lastRect.setBottomRight(e->pos());//不是拖拽时，更新矩形的右下角坐标)
            }

            _lpress = false;

        }
        else if(_drawType == 3)
        {
            QRect& lastEllipse = _ellipse.last();//拿到新椭圆
            if(!_drag)
            {
                lastEllipse.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
            }
            _lpress = false;
            update();
        }
        else if(_drawType == 4)
        {
            QRect& lastLine = _line.last();//拿到新直线
            if(!_drag)
            {
                lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            }
            _lpress = false;
        }
        else if(_drawType == 5)
        {
            cout <<"closing secCircle"<<endl;
            QRect& last = _arc.last();//拿到新圆弧
            last.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
            _lpress = false;
        }
        else if(_drawType == 6)
        {
            _arcCenter.pop_back();
            _lpress = false;
        }
        else if (_drawType == 7) {
            //多边形创建过程中会多次松开
//            _lpress = false;//标志左键释放
            update();
        }
        else if(_drawType == 8){
            _lpress = false;//标志左键释放
            update();
        }
        else if (_drawType == 9){
            _lpress = false;
        }
        else if (_drawType == 10){
            _lpress = false;
        }
        else if (_drawType == 11){
            _lpress = false;
            update();
        }
    }
}

void MyPaint::Lines()
{
    _drawType = 1;//铅笔
    _drag = 0;
}

void MyPaint::Line()
{
    _drawType = 4;//直线
    _drag = 0;
}

void MyPaint::Rects()
{
    _drawType = 2;//矩形
    _drag = 0;

}

void MyPaint::Ellipses()
{
    _drawType = 3;//椭圆
    _drag = 0;
}

void MyPaint::Arc()
{
    _drawType = 5;//圆弧
    _drag = 0;
}


void MyPaint::ArcCenter()
{
    _drawType = 6;//圆弧圆心
    _drag = 0;
}

void MyPaint::Polygon() {
    _drawType = 7;
    _drag = 0;
}

void MyPaint::Fill(){
    _drawType = 8;
    _drag = 0;

}

void MyPaint::Bezier() {
    _drawType = 9;
    _drag = 0;
}
void MyPaint::startMove(){
    _drawType = 10;
    _drag = 1;
}

void MyPaint::startFill(){
    _drawType = 11;
    _drag = 0;
}

void MyPaint::SavePic()
{
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0)
    {
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(0,30,size().width(),size().height()-30)).save(fileName);//不包含工具栏
    }
}

void MyPaint::OpenPic()
{
    //弹出文件打开对话框
    QString picPath = QFileDialog::getOpenFileName(this,tr("打开"),"","Image Files(*.jpg *.png)");
    if(!picPath.isEmpty())//用户选择了文件
    {
        QPixmap pix;
        pix.load(picPath);//加载图片
        QPainter p(&_pixmap);
        p.drawPixmap(0,30,pix);//添加工具栏的空间
        _openflag = 1;//设置文件打开标志
        update();//触发窗体重绘，将图片画到窗体
    }
}

void MyPaint::createBrushWindow(){
    emit sendPen(&_pen);
    setBrushWindow->show();
}



void MyPaint::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    _Rmenu->exec(cursor().pos());//在光标位置弹出菜单
}

void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
     //Ctrl+Z撤销
     if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
     {
         if(_shape.size()>0)
         {
             switch(_shape.last())
             {
                 case 1: _lines.pop_back();
                         break;
                 case 2: _rects.pop_back();
                         break;
                 case 3: _ellipse.pop_back();
                         break;
                 case 4: _line.pop_back();
                         break;
                 case 5: _arc.pop_back();
                         break;
                 case 6: _arcCenter.pop_back();
                         break;
             }
             _shape.pop_back();
             _drag = 0;//设置为非拖拽模式
             update();
         }
     }
     else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
     {
        SavePic();//Ctrl+S保存
     }
    else if (e->key() == Qt::Key_Escape) {
        if (_drawType == 7){
            update();
            _lpress = false;
            _newPolygon = true;
        }
         if (_drawType == 9){ // bezier控制点绘制结束
             _brush.append(_pen);
             _shape.append(9);
             _bezierCurve.push_back(_currentBezierCurve);
             vector <point2d>().swap(_currentBezierCurve);
             update();
         }
    }

}

int crossProduct(QPoint A, QPoint B, QPoint C){
    return (B.x() - A.x()) * (C.y() - A.y()) - (C.x() - A.x()) * (B.y() - A.y());
}

//判断点Q是否在P1和P2的线段上
bool OnSegment(QPoint P1,QPoint P2,QPoint Q)
{
    //前一个判断点Q在P1P2直线上 后一个判断在P1P2范围上
    //QP1 X QP2
    return crossProduct(Q,P1,P2)==0 && QPoint::dotProduct(P1-Q,P2-Q)<=0;
}
bool MyPaint::polyContains(QVector<QPoint> polygon, QPoint P){
    bool flag = false; //相当于计数
    QPoint P1,P2; //多边形一条边的两个顶点
    for(int i=0,j=polygon.length()-1;i<polygon.length();j=i++)
    {
        //polygon[]是给出多边形的顶点
        P1 = polygon[i];
        P2 = polygon[j];
        if(OnSegment(P1,P2,P)) return true; //点在多边形一条边上
        //前一个判断min(P1.y,P2.y)<P.y<=max(P1.y,P2.y)
        //后一个判断被测点 在 射线与边交点 的左边
        if( ((P1.y()-P.y())>0 != (P2.y()-P.y())>0) && (P.x() - (P.y()-P1.y())*(P1.x()-P2.x())/(P1.y()-P2.y())-P1.x())<0)
            flag = !flag;
    }
//    qDebug()<<"is in poly?"<<flag;
    return flag;
}
