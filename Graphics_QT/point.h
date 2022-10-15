#ifndef POINT_H
#define POINT_H
class point2d {
public:
    double x, y;
    point2d(){}
    point2d(double X, double Y):x(X), y(Y){}
    void seX(double X){x = X;}
    void seY(double Y){x = Y;}
};
#endif
