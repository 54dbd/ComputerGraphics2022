#ifndef FILL_H
#define FILL_H

#include <iostream>
#include <QPainter>
#include <QPoint>
#include <QStack>
#include <QColor>
#include <QImage>
#include <ctime>
#include <QDebug>
#include "Brush.h"

using namespace std;

class Fill: public Brush{
private:
    QStack<QPoint> stack;
    QPixmap &_pixmap;
    QPen &_pen;
    QColor tempColor;
public:
    Fill(QPixmap &map,QPainter &p, QPen &pen): Brush(1,p, pen), _pixmap(map),_pen(pen){

    }
    void fillColor(QColor color){
        tempColor = _pen.color();
        _pen.setColor(color);
    }
    void restoreColor(){
        _pen.setColor(tempColor);
    }

    void timeGetColor(){
       clock_t start,end;
       start = clock();
       qDebug()<<"start QT timing!";
        for(int i=0;i<600;i++){
            for(int j=0;j<400;j++){
                getPixelColor(i,j);
            }
        }
        end = clock();
        double endtime=(double)(end-start)/CLOCKS_PER_SEC;
        qDebug()<<"QT Total time:"<<endtime<<" s";		//s为单位

        start = clock();
        qDebug()<<"start MAP timing!";
         for(int i=0;i<600;i++){
             for(int j=0;j<400;j++){
                 MAP[i][j].getColor();
             }
         }
         end = clock();
         endtime=(double)(end-start)/CLOCKS_PER_SEC;
         qDebug()<<"MAP Total time:"<<endtime<<" s";		//s为单位
    }
    /*
     * point:填充起始点
     *
     * function: 填充任意封闭图形
     *
    */
    void fillShape(QPoint point, QColor newColor){
        //将点击位置的颜色设置为需要替换的颜色
        QColor oldColor = MAP[point.x()][point.y()].getColor();
        if(oldColor==newColor)
            return;
        //笔刷设置为需要的新颜色
        _pen.setColor(newColor);
        int xl,xr,i,x,y;
        x = point.x();
        y = point.y();
        bool spanNeedFill;
        QPoint pt(point);
        push(pt);
        while(!isEmpty()){
            pt = pop();
            y = pt.y();
            x = pt.x();
            while(MAP[x][y].getColor()==oldColor && x<599){
                drawPixel(x,y);
                x++;
            }
            xr = x -1;
            x = pt.x() - 1;
            while(MAP[x][y].getColor()==oldColor && x>0){
                drawPixel(x,y);
                x--;
            }
            xl = x + 1;
            x = xl;
            y = y + 1;
            while(x<xr){
                spanNeedFill = false;
                while(MAP[x][y].getColor()==oldColor && x<599){
                    spanNeedFill = true;
                    x++;

                }
                if(spanNeedFill){
                    pt.setX(x - 1);
                    pt.setY(y);
                    push(pt);
                    spanNeedFill= false;

                }
                while(MAP[x][y].getColor()!=oldColor&&x<xr)x++;
            }
            x = xl;
            y = y-2;
            while(x<xr){
                spanNeedFill = false;
                while(MAP[x][y].getColor()==oldColor && x<599){
                    spanNeedFill = true;
                    x++;

                }
                if(spanNeedFill){
                    pt.setX(x - 1);
                    pt.setY(y);
                    push(pt);
                    spanNeedFill= false;

                }
                while(MAP[x][y].getColor()!=oldColor&&x<xr)x++;
            }
        }
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

    void getColorMap() {
        QImage image = _pixmap.toImage();
        for(int i = 0;i < 600;i++){
            for(int j = 0;j < 400;j++){
                MAP[i][j].setColor(image.pixelColor(i,j));
            }
        }
    }

};

#endif // FILL_H
