//
// Created by Administrator on 30/10/2022.
//

#ifndef GRAPHICS_PLAYER_H
#define GRAPHICS_PLAYER_H
#include "point.h"
#include "Brush.h"

#include <QRect>
#include <QVector>


#define HEIGHT 16
#define WIDTH 9

class Player: public Brush {
private:
    QVector<QVector<int>> run1 = {
            {0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,0,1,1,1,1,0,0,1},
            {0,0,0,1,1,0,0,1,1},
            {0,1,1,1,1,1,1,1,0},
            {1,1,0,1,1,0,0,0,0},
            {1,0,0,1,1,0,0,0,0},
            {1,0,0,1,1,1,1,0,0},
            {0,0,1,1,0,0,1,0,0},
            {0,0,1,0,0,0,1,0,0},
            {0,1,1,0,0,1,1,0,0},
            {0,1,0,0,0,1,0,0,0},
            {0,1,0,0,0,0,0,0,0},
    };
    QVector<QVector<int>> run2 = {
            {0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,0,1,1,1,0,0,0},
            {0,0,0,1,1,1,1,0,0},
            {0,0,0,1,0,0,1,0,0},
            {0,0,0,1,0,0,1,0,0},
            {0,0,1,0,0,1,1,0,0},
            {0,0,1,0,0,1,0,0,0},
    };
    QVector<QVector<int>> run3 = {
            {0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,1,1,1,1,1,1,0,0},
            {0,0,1,1,1,1,0,0,0},
            {0,0,0,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,1,1,1,0,0,0,0},
            {0,0,0,1,1,0,0,0,0},
            {0,0,0,1,1,0,0,0,0},
            {0,0,0,1,1,0,0,0,0},
            {0,0,0,1,1,0,0,0,0},
    };
    QVector<QVector<int>> run4 = run2;
    QVector<QVector<pointData>> figure;             //人物造型
    QVector<QVector<QVector<int>>> sequence={run1,run2,run3,run4};   //动画序列 存放多个人物造型
    QRect collideBox;
    QPoint pos;
    int scale;
    QVector<int> speed={1,0};

public:
    Player(int W, QPainter& P, QPen& Pen, int x=100, int y=300):Brush(W,P,Pen) {
        pos.setX(x);
        pos.setY(y);
        scale = 2;
    }
    void generate(int num){
        QVector<QVector<int>> choice = sequence[num];
        for (int i = 0; i < HEIGHT*scale; i++) {
            for (int j = 0; j < WIDTH*scale; j++) {
                if (choice[i/2][j/2])
                    painter.drawPoint(pos.x() + j, pos.y() + i);
            }
        }
    }
    void setSpeed(int speedX,int speedY){
        speed[0]=speedX;
        speed[1]=speedY;
    }
    void update(int x, int y){
        pos.setX(x);
        pos.setY(y);
        qDebug()<<"pos:("<<pos.x()<<", "<<pos.y()<<")";
    }


};


#endif //GRAPHICS_PLAYER_H
