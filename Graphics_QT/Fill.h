#ifndef FILL_H
#define FILL_H

#include <iostream>
#include <QPainter>
#include <QPoint>
#include <QStack>
#include <QColor>
#include <QImage>
#include "Brush.h"

using namespace std;

class Fill: public Brush{
private:
    QStack<QPoint> stack;
    QPixmap _pixmap;
public:
    Fill(QPixmap &map,QPainter &p): Brush(1,p){
        _pixmap = map;
    }


    void push(QPoint p){
        stack.push(p);
    }

    QPoint pop(){
        return stack.pop();
    }

    bool isEmpty(){
        return stack.empty();
    }

    QColor getPixelColor(int x,int y){
        QImage image = _pixmap.toImage();
        return image.pixelColor(x,y);
    }

};

#endif // FILL_H
