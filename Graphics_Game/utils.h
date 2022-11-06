//
// Created by Administrator on 29/10/2022.
//

#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <QRect>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

extern vector<vector<pointData>> MAP;

int encode(int x, int y, int XL, int XR, int YB, int YT) {
    int c = 0;
    if (x < XL) c |= LEFT; // 置位CL
    if (x > XR) c |= RIGHT; // 置位CR
    if (y > YB) c |= BOTTOM; // 置位CB
    if (y < YT) c |= TOP; // 置位CT
    return c;
}

QRect CS_ClipLine(QRect line, int XL, int XR, int YB, int YT) {
    int x1 = line.topLeft().x();
    int x2 = line.bottomRight().x();
    int y1 = line.topLeft().y();
    int y2 = line.bottomRight().y();

    int x, y;
    int code1, code2, code;
    // 端点坐标编码
    code1 = encode(x1, y1, XL, XR, YB, YT);
    code2 = encode(x2, y2, XL, XR, YB, YT);
    // 直到”完全可见”为止
    while (code1 != 0 || code2 != 0) {
        // 排除”显然不可见”情况
        if ((code1 & code2) != 0)
            return QRect(-1, -1, -1, -1);
        code = code1;
        // 求得在窗口外的点
        if (code1 == 0)
            code = code2;
        // 按顺序检测到端点的编码不为0，才把线段与对应的窗口边界求交。
        if ((LEFT & code) != 0) { // 线段与窗口左边延长线相交
            x = XL;
            y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
        } else if ((RIGHT & code) != 0) { // 线段与窗口右边延长线相交
            x = XR;
            y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
        } else if ((BOTTOM & code) != 0) { // 线段与窗口下边延长线相交
            y = YB;
            x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
        } else if ((TOP & code) != 0) { // 线段与窗口上边延长线相交
            y = YT;
            x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
        }
        if (code == code1) { //裁去P1到交点
            x1 = x;
            y1 = y;
            code1 = encode(x1, y1, XL, XR, YB, YT);
        } else {  //裁去P2到交点
            x2 = x;
            y2 = y;
            code2 = encode(x2, y2, XL, XR, YB, YT);
        }
    }
    QPoint topLeft(x1, y1), bottomRight(x2, y2);
    QRect rect;//鼠标按下，直线一端开始
    rect.setTopLeft(topLeft);
    rect.setBottomRight(bottomRight);
    return rect;
}

QRect MidPoint_ClipLine(QRect line, int XL, int XR, int YB, int YT) {
    int x1 = line.topLeft().x();
    int x2 = line.bottomRight().x();
    int y1 = line.topLeft().y();
    int y2 = line.bottomRight().y();

    int xa = x1, ya = y1, xb = x2, yb = y2;
    int code1, code2, code_m;
    // 端点坐标编码
    code1 = encode(x1, y1, XL, XR, YB, YT);
    code2 = encode(x2, y2, XL, XR, YB, YT);

    // 两个点都在窗口内，显然可见，直接返回直线
    if (code1 == 0 && code2 == 0) {
        return line;
    }
        // 两个点都在窗口外，显然不可见，直接返回空
    else if ((code1 & code2) != 0) {
        return QRect(-1, -1, -1, -1);
    }
    // 对于剩下的情况，需要使用中点算法
    // 首先先求P1点最近的窗口边界点Pa点
    if (code1 != 0) {
        int x_0 = x1, y_0 = y1, x_1 = x2, y_1 = y2;
        int code_0 = encode(x_0, y_0, XL, XR, YB, YT);
        int code_1 = encode(x_1, y_1, XL, XR, YB, YT);
        while (true) {
            int xm = (x_0 + x_1) / 2;
            int ym = (y_0 + y_1) / 2;
            int distance;
            code_m = encode(xm, ym, XL, XR, YB, YT);
            if ((code_0 & code_m) == 0) {
                x_1 = xm;
                y_1 = ym;
                code_1 = code_m;
            } else {
                x_0 = xm;
                y_0 = ym;
                code_0 = code_m;
            }
            if ((x_1 - x_0) * (x_1 - x_0) + (y_1 - y_0) * (y_1 - y_0) <= 4) {
                xa = xm;
                ya = ym;
                break;
            }
        }
    }
    // 随后求P2点最近的窗口边界点Pb点
    if (code2 != 0) {
        int x_0 = x1, y_0 = y1, x_1 = x2, y_1 = y2;
        int code_0 = encode(x_0, y_0, XL, XR, YB, YT);
        int code_1 = encode(x_1, y_1, XL, XR, YB, YT);
        while (true) {
            int xm = (x_0 + x_1) / 2;
            int ym = (y_0 + y_1) / 2;
            code_m = encode(xm, ym, XL, XR, YB, YT);
            if ((code_1 & code_m) == 0) {
                x_0 = xm;
                y_0 = ym;
                code_0 = code_m;
            } else {
                x_1 = xm;
                y_1 = ym;
                code_1 = code_m;
            }
            if ((x_1 - x_0) * (x_1 - x_0) + (y_1 - y_0) * (y_1 - y_0) <= 4) {
                xb = xm;
                yb = ym;
                break;
            }
        }
    }
    QPoint topLeft(xa, ya), bottomRight(xb, yb);
    return QRect(topLeft, bottomRight);
}

int crossProduct(QPoint A, QPoint B, QPoint C) {
    return (B.x() - A.x()) * (C.y() - A.y()) - (C.x() - A.x()) * (B.y() - A.y());
}

//判断点Q是否在P1和P2的线段上
bool OnSegment(QPoint P1, QPoint P2, QPoint Q) {
    //前一个判断点Q在P1P2直线上 后一个判断在P1P2范围上
    //QP1 X QP2
    return crossProduct(Q, P1, P2) == 0 && QPoint::dotProduct(P1 - Q, P2 - Q) <= 0;
}

double Area(QPoint p0, QPoint p1, QPoint p2) {
    double area = 0;
    area = p0.x() * p1.y() + p1.x() * p2.y() + p2.x() * p0.y() - p1.x() * p0.y() - p2.x() * p1.y() - p0.x() * p2.y();
    return area / 2;
}

QPoint getPolyCenter(QVector<QPoint> Poly) {
    QPoint p0 = Poly[0];
    QPoint p1 = Poly[1];
    QPoint p2;
    int Center_X, Center_Y;
    double sumarea = 0, sumx = 0, sumy = 0;
    double area;
    for (int i = 2; i < Poly.size(); i++) {
        p2 = Poly[i];
        area = Area(p0, p1, p2);
        sumarea += area;
        sumx += (p0.x() + p1.x() + p2.x()) * area; //求∑cx[i] * s[i]和∑cy[i] * s[i]
        sumy += (p0.y() + p1.y() + p2.y()) * area;
        p1 = p2;//求总面积
    }
    Center_X = (int) (sumx / sumarea / 3.0);
    Center_Y = (int) (sumy / sumarea / 3.0);
    qDebug() << Center_X;
    qDebug() << Center_Y;
    return QPoint(Center_X, Center_Y);

    /*double Cx = 0,Cy = 0;
    for(QPoint q :Poly){
        Cx += q.x();
        Cy += q.y();
    }
    Cx /= Poly.size();
    Cy /= Poly.size();
    return QPoint((int)Cx,(int)Cy);*/
}

double getAngle(QPoint origin, QPoint p1, QPoint p2) {
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x(), y2 = p2.y(), x3 = origin.x(), y3 = origin.y();
    double theta = atan2(x1 - x3, y1 - y3) - atan2(x2 - x3, y2 - y3);

    if (theta > M_PI)
        theta -= 2 * M_PI;
    if (theta < -M_PI)
        theta += 2 * M_PI;

    theta = abs(theta * 180.0 / M_PI);
    if ((x2 - x3) * (y2 - y1) - (y2 - y3) * (x2 - x1) < 0)
        theta *= -1;
    return theta;
}

void MyPaint::setDashLine(Qt::PenStyle style) {//设置虚线变量
    qDebug() << "style:" << style;
    if (style == Qt::DashLine) {
        isDashLine = true;
    } else {
        isDashLine = false;
    }
}

void MyPaint::updateCoordiante(int x, int y) {
    QString output = "当前坐标(" + QString::number(x, 10) + ", " + QString::number(y, 10) + ")";
    statusBarLabel->setText(output);
}

bool polyContains(QVector<QPoint> polygon, QPoint P) {
    bool flag = false; //相当于计数
    QPoint P1, P2; //多边形一条边的两个顶点
    for (int i = 0, j = polygon.length() - 1; i < polygon.length(); j = i++) {
        //polygon[]是给出多边形的顶点
        P1 = polygon[i];
        P2 = polygon[j];
        if (OnSegment(P1, P2, P)) return true; //点在多边形一条边上
        //前一个判断min(P1.y,P2.y)<P.y<=max(P1.y,P2.y)
        //这个判断代码我觉得写的很精妙 我网上看的 应该是大神模版
        //后一个判断被测点 在 射线与边交点 的左边
        if (((P1.y() - P.y()) > 0 != (P2.y() - P.y()) > 0) &&
            (P.x() - (P.y() - P1.y()) * (P1.x() - P2.x()) / (P1.y() - P2.y()) - P1.x()) < 0)
            flag = !flag;
    }
//    qDebug()<<"is in poly?"<<flag;
    return flag;
}

QPoint intersection(QPoint p1, QPoint p2, QPoint p3, QPoint p4) {
    QPoint p;
    double a1, b1, c1, a2, b2, c2, x, y;
    a1 = p2.y() - p1.y();
    b1 = p1.x() - p2.x();
    c1 = p2.x() * p1.y() - p1.x() * p2.y();
    a2 = p4.y() - p3.y();
    b2 = p3.x() - p4.x();
    c2 = p4.x() * p3.y() - p3.x() * p4.y();
    x = int((b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1));
    y = int((a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1));
    if ((x <= max(p1.x(), p2.x()) && x >= min(p1.x(), p2.x()))) {
        p.setX(x);
        p.setY(y);
        return p;
    } else {
        return QPoint(-1, -1);
    }
}

bool outsideOneEdgeOfPolygon(QVector<QPoint> polygon, QPoint p, int x) {
    QPoint p1 = polygon[x];
    QPoint p2 = polygon[(x + 1) % int(polygon.length())];
    QPoint p3 = polygon[(x + 2) % int(polygon.length())];
    int a = p2.y() - p1.y();
    int b = p1.x() - p2.x();
    int c = p2.x() * p1.y() - p1.x() * p2.y();
    if (a < 0) {
        a = -a;
        b = -b;
        c = -c;
    }
    int pointD = a * p.x() + b * p.y() + c;
    int polyNextPointD  = a * p3.x() + b * p3.y() + c;
    if (pointD * polyNextPointD >= 0) {
        return true;
    } else {
        return false;
    }
}

QVector<QPoint> cropPolygon(const QVector<QPoint>& polygon, const QVector<QPoint>& cropPolygon) {
    QVector<QPoint> result, originalPolygon = polygon;
    for (int i = 0; i < cropPolygon.length(); ++i) {
        result.clear();
        for (int j = 0; j < originalPolygon.length(); ++j) {
            QPoint p1 = originalPolygon[j];
            QPoint p2 = originalPolygon[(j + 1) % int(originalPolygon.length())];
            bool p1_inPolygonEdge = outsideOneEdgeOfPolygon(cropPolygon, p1, i);
            bool p2_inPolygonEdge = outsideOneEdgeOfPolygon(cropPolygon, p2, i);
            if (p1_inPolygonEdge && p2_inPolygonEdge) {
                result.append(p2);
            } else if (p1_inPolygonEdge || p2_inPolygonEdge) {
                QPoint k1 = cropPolygon[i];
                QPoint k2 = cropPolygon[(i + 1) % int(cropPolygon.length())];
                QPoint temp = intersection(p1, p2, k1, k2);
                if (temp.x() != -1 && temp.y() != -1) {
                    result.append(temp);
                }
            }
            if (!p1_inPolygonEdge && p2_inPolygonEdge) {
                result.append(p2);
            }
        }
        originalPolygon = result;
    }
    return result;
}

void initMAP(){
    for (int i = 0; i < 600; i++) {
        vector<pointData> row;
        MAP.push_back(row);
        for (int j = 0; j < 400; j++) {
            //对每一行中的每一列进行添加点
            pointData point(QPoint(i, j), Qt::white);
            MAP[i].push_back(point);
        }
    }
}
bool canJump(int playerX, int playerY){
    if(MAP[playerX+8][playerY+32].getColor()==Qt::black
       ||MAP[playerX+8][playerY+33].getColor()==Qt::black
       ||MAP[playerX+9][playerY+32].getColor()==Qt::black
       ||MAP[playerX+9][playerY+33].getColor()==Qt::black
       ||MAP[playerX+10][playerY+32].getColor()==Qt::black
       ||MAP[playerX+10][playerY+33].getColor()==Qt::black
            ){
        return true;
    }
    return false;
}

bool canDrop(int playerX, int playerY){
    //x,y从人物左上角开始算,人物高32（16*2）。脚底为x+9，y+32
//    qDebug()<<"player at: "<<playerX<<","<<playerY;
//    qDebug()<<"ground at: "<<playerX+5<<","<<playerY+32<<" COLOR:"<<MAP[playerX+5][playerY+32].getColor();
    //检测两格
    if(MAP[playerX+8][playerY+32].getColor()==Qt::black
    ||MAP[playerX+8][playerY+33].getColor()==Qt::black
    ||MAP[playerX+9][playerY+32].getColor()==Qt::black
    ||MAP[playerX+9][playerY+33].getColor()==Qt::black
    ||MAP[playerX+10][playerY+32].getColor()==Qt::black
    ||MAP[playerX+10][playerY+33].getColor()==Qt::black
    ){
//        qDebug()<<"ground at: "<<playerX+5<<","<<playerY+32;
        return false;
    }
    return true;
}
bool isDie(int playerX, int playerY){
    if(MAP[playerX+8][playerY+32].getColor()==Qt::red
       ||MAP[playerX+8][playerY+33].getColor()==Qt::red
       ||MAP[playerX+9][playerY+32].getColor()==Qt::red
       ||MAP[playerX+9][playerY+33].getColor()==Qt::red
       ||MAP[playerX+10][playerY+32].getColor()==Qt::red
       ||MAP[playerX+10][playerY+33].getColor()==Qt::red
       ||MAP[playerX+8][playerY].getColor()==Qt::red
       ||MAP[playerX+8][playerY-1].getColor()==Qt::red
       ||MAP[playerX+9][playerY].getColor()==Qt::red
       ||MAP[playerX+9][playerY-1].getColor()==Qt::red
       ||MAP[playerX+10][playerY].getColor()==Qt::red
       ||MAP[playerX+10][playerY-1].getColor()==Qt::red
            ) {
        return true;
    }
    return false;

}


bool  canWalkRight(int playerX, int playerY){
    if(MAP[playerX+10][playerY+30].getColor()==Qt::black
      ||MAP[playerX+11][playerY+30].getColor()==Qt::black
      ||MAP[playerX+12][playerY+30].getColor()==Qt::black
      ||MAP[playerX+13][playerY+30].getColor()==Qt::black
      ||MAP[playerX+14][playerY+30].getColor()==Qt::black
      ||MAP[playerX+10][playerY+31].getColor()==Qt::black
      ||MAP[playerX+11][playerY+31].getColor()==Qt::black
      ||MAP[playerX+12][playerY+31].getColor()==Qt::black
      ||MAP[playerX+13][playerY+31].getColor()==Qt::black
      ||MAP[playerX+14][playerY+31].getColor()==Qt::black
      ){
        return false;
    }
    return true;
}

bool canWalkLeft(int playerX, int playerY){
    if(MAP[playerX+3][playerY+31].getColor()==Qt::black
       ||MAP[playerX+4][playerY+31].getColor()==Qt::black
       ||MAP[playerX+5][playerY+31].getColor()==Qt::black
       ||MAP[playerX+6][playerY+31].getColor()==Qt::black
       ||MAP[playerX+7][playerY+31].getColor()==Qt::black
       ||MAP[playerX+3][playerY+30].getColor()==Qt::black
       ||MAP[playerX+4][playerY+30].getColor()==Qt::black
       ||MAP[playerX+5][playerY+30].getColor()==Qt::black
       ||MAP[playerX+6][playerY+30].getColor()==Qt::black
       ||MAP[playerX+7][playerY+30].getColor()==Qt::black){
        return false;
    }
    return true;
}

bool noRightWall(int playerX, int playerY){
    if(MAP[playerX+10][playerY+15].getColor()==Qt::black
       ||MAP[playerX+11][playerY+15].getColor()==Qt::black
       ||MAP[playerX+12][playerY+15].getColor()==Qt::black
       ||MAP[playerX+13][playerY+15].getColor()==Qt::black
       ||MAP[playerX+14][playerY+15].getColor()==Qt::black){
        return false;
    }
    return true;
}
bool noLeftWall(int playerX, int playerY){
    if(MAP[playerX+3][playerY+15].getColor()==Qt::black
       ||MAP[playerX+4][playerY+15].getColor()==Qt::black
       ||MAP[playerX+5][playerY+15].getColor()==Qt::black
       ||MAP[playerX+6][playerY+15].getColor()==Qt::black
       ||MAP[playerX+7][playerY+15].getColor()==Qt::black){
        return false;
    }
    return true;
}
void MyPaint::cleanScreen(){
    _lpress = false;//初始鼠标左键未按下
    _newPolygon = true;//代表多边形可以新建
    _drag = 0;//默认非拖拽模式
    _drawType = 0;//初始为什么都不画
    _begin = pos();//拖拽的参考坐标，方便计算位移
    _openflag = 0;//初始不打开图片
    _transFlag = NOTRANS;
    _lines.clear();
    _rects.clear();//矩形集合
    _ellipse.clear();//椭圆集合
    _line.clear();//直线集合
    _arc.clear();//圆弧集合
    _transRect.clear();  //旋转矩形集合
    _arcCenter.clear();
    _polygon.clear();//多边形集合
    _fill.clear();
    _cropPolygon.clear();// 裁切多边形
    k_steps.clear();
    _shape.clear();//图形类型集合，用于撤回功能
    _brush.clear();
    isInRect = 0;
    isInEllipse = 0;
    isInPolygon = 0;
    isInFill = 0;
    playerX = spawnX[stageNumber-1];
    playerY = spawnY[stageNumber-1];
    _playerStatus = ALIVE;
    //初始化MAP
    initMAP();
    state=IDLE;
    update();
}

bool hasCollision(QPoint p1, QPoint p2) {
    double distance = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
    if (distance <= 20) {
        return true;
    } else {
        return false;
    }
}


#endif //GRAPHICS_UTILS_H
