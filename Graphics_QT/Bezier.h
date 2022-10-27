#ifndef BEZIER_H
#define BEZIER_H
#include <iostream>
#include <QPainter>
#include <QPoint>
#include <cmath>
#include "Brush.h"
#include "point.h"
#include "Line.h"
using namespace std;

class Bezier: public Brush
{
public:
    Bezier(int penWidth, QPainter &p, vector<QPoint> points, QPen pen): Brush(penWidth, p, pen){
        for (int i = 0; i < points.size(); ++i) {
            controlPoints.emplace_back(double(points[i].x()),double(points[i].y()));
        }
    }
    point2d recursive_bezier(const std::vector<point2d> &control_points, double t)
    {
        // Casteljau
        int n = control_points.size();
        if (n == 1) return control_points[0];
        std::vector<point2d> res;
        for (int i = 0; i < n - 1; ++i) {
            res.emplace_back((1 - t) * control_points[i].x + t * control_points[i + 1].x, (1 - t) * control_points[i].y + t * control_points[i + 1].y);
        }
        return recursive_bezier(res, t);
    }

    void drawBezier()
    {
        point2d last_p = recursive_bezier(controlPoints, 0);
        for (int i = 1; i <= 1000; i += 1) {
            double current_t = double(i) / 1000;
            point2d p = recursive_bezier(controlPoints, current_t);
//            drawPixel(round(p.x), round(p.y));
            int x_s = round(last_p.x);
            int x_e = round(p.x);
            int y_s = round(last_p.y);
            int y_e = round(p.y);
            //创建直线
            class Line l(x_s,y_s,x_e,y_e,1, painter, _pen);
            l.MidPoint();

            last_p = p;
        }
    }
private:
    vector<point2d> controlPoints;
};

#endif
