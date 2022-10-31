#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Brush.h"
#include <iostream>
#include <QPainter>
#include <math.h>
using namespace std;



class Circle : public Brush
{
private:
    int cx, cy, r;
    QColor color;
    QPen _pen;

    void CirclePoint(int x, int y) {
        drawPixel(x + cx, y + cy);
        drawPixel(y + cx, x + cy);
        drawPixel(-x + cx, y + cy);
        drawPixel(y + cx, -x + cy);
        drawPixel(x + cx, -y + cy);
        drawPixel(-y + cx, x + cy);
        drawPixel(-x + cx, -y + cy);
        drawPixel(-y + cx, -x + cy);


    }

public:
    Circle(int X, int Y, int R ,int W, QPainter &p, QPen pen):Brush(W,p,pen) {
        cx = X;
        cy = Y;
        r = R;
        _pen = pen;
    }

    void SetCenter(int X, int Y) {
        cx = X;
        cy = Y;

    }

    void SetR(int R) {
        r = R;
    }

    void DrawCircle() {
        int x, y, d, e;
        x = 0;
        y = r;
        e = 1 - r;
        CirclePoint(x, y);
        while (x <= y) {
            if (e < 0)
                e += 2 * x + 3;
            else {
                e += 2 * (x - y) + 5;
                y--;
            }
            x++;
            CirclePoint(x,y);
        }

    }

    void DrawDashLIneCircle() {
        int x, y, e,ct=0;
        x = 0;
        y = r;
        e = 1 - r;
        CirclePoint(x, y);
        while (x <= y) {
            if (e < 0)
                e += 2 * x + 3;
            else {
                e += 2 * (x - y) + 5;
                y--;
            }
            x++;
            //虚线处理
            if (ct % 31 > 15) {
                CirclePoint(x, y);
            }
            ct++;
        }

    }

};


#endif
