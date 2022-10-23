#ifndef POINT_H
#define POINT_H
#include <QPoint>
#include <QColor>
class pointData{
protected:
    QPoint pos;
    QColor color;
public:
    pointData(QPoint p, QColor c){
        pos = p;
        color = c;
    }
    QColor getColor(){
        return color;
    }
    void setColor(QColor c){
        color = c;
    }
};
class point2d {
public:
    double x, y;
    point2d(){}
    point2d(double X, double Y):x(X), y(Y){}
    void seX(double X){x = X;}
    void seY(double Y){x = Y;}
};
#endif
