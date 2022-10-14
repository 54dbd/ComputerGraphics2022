#ifndef BEZIER_H
#define BEZIER_H
#include <iostream>
#include <QPainter>
#include <cmath>
#include "Brush.h"
#include "point.h"
using namespace std;

class Bezier: public Brush
{
public:
    Bezier(int penWidth, QPainter &p, vector<point2d> points): Brush(penWidth, p){
        controlPoints = points;
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
        for (int i = 0; i <= 1000; i += 1) {
            double current_t = double(i) / 1000;
            point2d p = recursive_bezier(controlPoints, current_t);
            drawPixel(round(p.x), round(p.y));
        }
    }
private:
    vector<point2d> controlPoints;
};

#endif
