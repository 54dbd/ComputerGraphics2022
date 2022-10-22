#ifndef BRUSH_H
#define BRUSH_H
#include <vector>
#include <QColor>
#include <QPainter>
#include <QPen>
#define COLORREF QColor
using namespace std;
class Brush
{
private:
    vector<vector<int>>const* brush;
    COLORREF color;
    QPainter &painter;
public:
    //方块刷_9
    const vector<vector<int>> brush_9 = {
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1},
    };
    //圆刷_7
    const vector<vector<int>> brush_7_r = {
        {0,0,1,1,1,0,0},
        {0,1,1,1,1,1,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {0,1,1,1,1,1,0},
        {0,0,1,1,1,0,0},

    };
    //X刷_7
    const vector<vector<int>> brush_7 = {
        {1,1,0,0,0,0,1},
        {0,1,1,0,0,1,1},
        {0,0,1,1,1,1,0},
        {0,0,0,1,1,0,0},
        {0,0,1,1,1,1,0},
        {0,1,1,0,0,1,1},
        {1,1,0,0,0,0,1},

    };
    //X刷_5
    const vector<vector<int>> brush_5 = {
        {1,1,0,0,1},
        {0,1,1,1,1},
        {0,0,1,1,0},
        {0,1,1,1,1},
        {1,1,0,0,1}
    };
    //X刷_3
    const vector<vector<int>> brush_3 = {
        {1,0,1},
        {0,1,0},
        {1,0,1}
    };
    //1刷
    const vector<vector<int>> brush_1 = {
        {1,},
    };
    Brush(int W, QPainter &p):painter(p) {
        setBrushType(W);
        //不使用QT内置笔刷宽度控制，如果有需要可以在这里开启
        //painter.setPen(QPen(C,W));
        //painter.setPen(QPen(C,1));
    };

    int setColor(COLORREF C) {
        color = C;
        return 0;
    };

    COLORREF getColor() {
        return color;
    }
    int setBrushType(int W) {
        switch (W)
        {
        case 1:
            brush = &brush_1;
            break;
        case 3:
            brush = &brush_3;
            break;
        case 5:
            brush = &brush_5;
            break;
        case -7:
            brush = &brush_7_r;
            break;
        case 7:
            brush = &brush_7;
            break;
        case 9:
            brush = &brush_9;
            break;
        default:
            brush = &brush_3;
            break;
        }
        return 1;
    };
    void drawPixel(int x, int y) {
//        for (int i = 0; i < (*brush).size(); i++) {
//            for (int j = 0; j < (*brush).size(); j++) {
//                if ((*brush)[i][j]) painter.drawPoint(x + i, y + j);

//            }
//        }
        //不使用笔刷
        painter.drawPoint(x, y);
    };
};


#endif // BRUSH_H
