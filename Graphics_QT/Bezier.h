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

//int k = 3;
//int n = 0;
//double *u;
class Bspline: public Brush
{
public:
    Bspline(int penWidth, QPainter &p, vector<QPoint> points, int k, QPen pen): Brush(penWidth, p, pen)
    {
        for (int i = 0; i < points.size(); ++i) {
            controlPoints.emplace_back(double(points[i].x()),double(points[i].y()));
        }
        k_step = k;
        n = controlPoints.size() - 1; // n + 1 控制点
        U = nullptr;
    }
    double coefficient(int i, int r, double u)
    {
        if (fabs(U[i + k_step - r] - U[i]) <= 1e-7)
            return 0;
        else
        {
            return (u - U[i]) / (U[i + k_step -r] - U[i]);
        }
    }
    double DeBoor_Cox_X(int i, int r, double u)
    {
        if (r == 0)
        {
            return controlPoints[i].x;
        }
        else
        {
            return coefficient(i, r, u) * DeBoor_Cox_X(i, r-1, u) + (1 - coefficient(i, r, u)) * DeBoor_Cox_X(i-1, r-1, u);
        }
    }
    double DeBoor_Cox_Y(int i, int r, double u)
    {
        if (r == 0)
        {
            return controlPoints[i].y;
        }
        else
        {
            return coefficient(i, r, u) * DeBoor_Cox_Y(i, r-1, u) + (1 - coefficient(i, r, u)) * DeBoor_Cox_Y(i-1, r-1, u);
        }
    }
    void drawBspline()
    {
        U = new double[n + k_step + 2];
        for (int i = 0; i < n + k_step + 2; ++i) {
//            U[i] = static_cast<double>(i / (n + k_step));
            U[i] = i; // 均匀即可 所有控制点的权重求和为1
        }
        double step = 0.0005;
        for (int i = k_step - 1; i < n + 1; ++i) {
            for (double theta_u = U[i]; theta_u < U[i+1]; theta_u += step) {
                int temp_x = round(DeBoor_Cox_X(i, k_step - 1, theta_u));
                int temp_y = round(DeBoor_Cox_Y(i, k_step - 1, theta_u));
                drawPixel(temp_x, temp_y);
            }
        }
        delete[] U;
    }
//    double getLambda(int i, int r, double t) {
//        if (fabs(u[i + k - r] - u[i]) <= 1e-7) {
//            return 0;
//        }
//        else {
//            return (t - u[i]) / (u[i + k - r] - u[i]);
//        }
//    }
////使用de Boor Cox递推公式来分别递归计算点的x，y坐标
//    double deBoorCox_X(int i, int r, double t) {
//        if (r == 0) return controlPoints[i].x;
//        else {
//            return getLambda(i, r, t)*deBoorCox_X(i, r - 1, t) + (1 - getLambda(i, r, t))*deBoorCox_X(i - 1, r - 1, t);
//        }
//    }
//    double deBoorCox_Y(int i, int r, double t) {
//        if (r == 0) return controlPoints[i].y;
//        else {
//            return getLambda(i, r, t)*deBoorCox_Y(i, r - 1, t) + (1 - getLambda(i, r, t))*deBoorCox_Y(i - 1, r - 1, t);
//        }
//    }
////根据参数得出B-spline曲线
//    void drawBspline() {
//
//        u = new double[n + k + 2];
//        for (int i = 0; i <= n + k + 1; i++) {
//            u[i] = i;
//        }
//        //在区间u(k-1)~u(n+1)，分割区间计算
//        double step = 0.0005;
//        for (int j = k - 1; j < n + 1; j++) {
//            for (double t = u[j]; t < u[j + 1]; t += step) {
//                int x = qRound(deBoorCox_X(j, k - 1, t));
//                int y = qRound(deBoorCox_Y(j, k - 1, t));
//                drawPixel(x, y);}
//        }
//        delete[] u;
//    }
private:
    vector<point2d> controlPoints;
    int k_step; // k阶 需要自定义
    int n; // n + 1控制点（屏幕上画出）
    double * U; // 节点向量
};


#endif
