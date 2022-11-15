#ifndef __Arc_H__
#define __Arc_H__
#include <iostream>
#include <math.h>
#include "Brush.h"
#include <math.h>
#include <QPainter>
#define PUTPIXELX(x,y,boder1,boder2)               if(x>=boder1&&x<=boder2)  \
                                                              drawPixel(x,y);



#define PUTPIXELY(x,y,boder1,boder2)                 if(y>=boder1&&y<=boder2)  \
                                                              drawPixel(x, y);


class Arc: public Brush
{
private:
    int cx, cy, r;

    void ArcPointX(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {

        PUTPIXELX(x + cx, y + cy, Borderup, Borderup2);
        PUTPIXELX(y + cx, x + cy, Borderup, Borderup2);
        PUTPIXELX(-x + cx, y + cy, Borderup, Borderup2);
        PUTPIXELX(y + cx, -x + cy, Borderdown, Borderdown2);
        PUTPIXELX(x + cx, -y + cy, Borderdown, Borderdown2);
        PUTPIXELX(-y + cx, x + cy, Borderup, Borderup2);
        PUTPIXELX(-x + cx, -y + cy, Borderdown, Borderdown2);
        PUTPIXELX(-y + cx, -x + cy, Borderdown, Borderdown2);


    }

    void ArcPointY(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {

        PUTPIXELY(x + cx, y + cy, Borderup, Borderup2);
        PUTPIXELY(y + cx, x + cy, Borderup, Borderup2);
        PUTPIXELY(-x + cx, y + cy, Borderdown, Borderdown2);
        PUTPIXELY(y + cx, -x + cy, Borderup, Borderup2);
        PUTPIXELY(x + cx, -y + cy, Borderup, Borderup2);
        PUTPIXELY(-y + cx, x + cy, Borderdown, Borderdown2);
        PUTPIXELY(-x + cx, -y + cy, Borderdown, Borderdown2);
        PUTPIXELY(-y + cx, -x + cy, Borderdown, Borderdown);


    }
    void ArcPointN(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {
        if ((Borderdown - cx) < 0) {
            PUTPIXELY(-x + cx, y + cy, Borderup, Borderup2);
            PUTPIXELY(-y + cx, x + cy, Borderup, Borderup2);
            PUTPIXELY(-x + cx, -y + cy, Borderup, Borderup2);
            PUTPIXELY(-y + cx, -x + cy, Borderup, Borderup2);
        }
        else {
            PUTPIXELY(x + cx, y + cy, Borderup, Borderup2);
            PUTPIXELY(y + cx, x + cy, Borderup, Borderup2);
            PUTPIXELY(y + cx, -x + cy, Borderup, Borderup2);
            PUTPIXELY(x + cx, -y + cy, Borderup, Borderup2);
        }

    }

    //对圆弧跨越x轴的情况做初始化与预处理
    void ConfigX(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2) {
        if (x2 < (2 * cx - x1)) {    //说明原点在弦右侧，则对应劣弧的最左界限为 -r
            Borderup = cx - r;
            Borderdown = cx - r;
            if ((y2 - cy) > 0) {        //此时y1与y2必有一个位于x轴上方，如果是y2在上方，则对于圆弧在x轴上方的部分，其右界为x2,下方的部分右界为x1
                Borderup2 = x2;
                Borderdown2 = x1;
            }
            else {
                Borderup2 = x1;
                Borderdown2 = x2;
            }
        }
        else {                         //与上述情况相反
            Borderup2 = cx + r;
            Borderdown2 = cx + r;
            if ((y2 - cy) > 0) {
                Borderup = x2;
                Borderdown = x1;
            }
            else {
                Borderup = x1;
                Borderdown = x2;
            }
        }
    }
    //对圆弧跨越y轴的情况做初始化与预处理，具体逻辑与ConfigX一致
    void ConfigY(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2) {
        if (y2 < (2 * cy - y1)) {
            Borderup = cy - r;
            Borderdown = cy - r;
            if ((x2 - cx) > 0) {
                Borderup2 = y2;
                Borderdown2 = y1;
            }
            else {
                Borderup2 = y1;
                Borderdown2 = y2;
            }
        }
        else {
            Borderup2 = cy + r;
            Borderdown2 = cy + r;
            if ((x2 - cx) > 0) {
                Borderup = y2;
                Borderdown = y1;
            }
            else {
                Borderup = y1;
                Borderdown = y2;
            }
        }
    }


    //总配置与预处理函数
    void ArcConfig(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2, int& flag) {
        if ((cy - y1) * (cy - y2) < 0) {      //此处判断是否跨越x轴
            flag = 1;
            ConfigX(x1, y1, x2, y2, Borderup, Borderup2, Borderdown, Borderdown2); //对跨越x轴的情况进行预处理
        }
        else if ((cx - x1) * (cx - x2) < 0) {  //是否跨越y轴
            flag = 2;
            ConfigY(x1, y1, x2, y2, Borderup, Borderup2, Borderdown, Borderdown2); //对跨越y轴的情况进行预处理
        }
        else {                       //圆弧只在一个象限
            flag = 0;
            if (y1 < y2) {
                Borderdown = x1;
                Borderup = y1;
                Borderup2 = y2;          //选择y做边界
            }
            else {
                Borderdown = x1;
                Borderup = y2;
                Borderdown2 = Borderup2 = y1;
            }
        }

    }

public:
    Arc(int X, int Y, int R, int W, QPainter& p, QPen pen) :Brush(W, p, pen) {
        cx = X;
        cy = Y;
        r = R;
    }

    void SetCenter(int X, int Y) {
        cx = X;
        cy = Y;

    }

    void SetR(int R) {
        r = R;
    }


    void DrawArc(int x1, int y1, int x2, int y2) {       //绘制任意圆弧，其实现的过程概括而言，是当绘制一个点时，根据预处理得到的一段圆弧的起点与终点来判断该点，以及该点在其他7个1/2象限的映射是否处于圆弧内
        int x, y, d, e, Borderup, Borderup2, Borderdown1, Borderdown2, flag;         //进一步分为三种情况，圆弧跨越y轴，圆弧跨越x轴，或不跨越任何坐标轴。前两种情况有重叠的部分，但并不影响
        ArcConfig(x1, y1, x2, y2, Borderup, Borderup2, Borderdown1, Borderdown2, flag);   //初始配置函数，区分三种情况并配置需要的界限
        x = 0;
        y = r;
        e = 1 - r;
        if (flag == 1) {
            while (x <= y) {
                if (e < 0)
                    e += 2 * x + 3;
                else {
                    e += 2 * (x - y) + 5;
                    y--;
                }
                x++;
                ArcPointX(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);

            }
        }
        else if (flag == 2) {
            while (x <= y) {
                if (e < 0)
                    e += 2 * x + 3;
                else {
                    e += 2 * (x - y) + 5;
                    y--;
                }
                x++;
                ArcPointY(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);
            }

        }
        else if (flag == 0) {
            while (x <= y) {
                if (e < 0)
                    e += 2 * x + 3;
                else {
                    e += 2 * (x - y) + 5;
                    y--;
                }
                x++;
                ArcPointN(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);

            }
        }
    }


};


#endif
#pragma once
