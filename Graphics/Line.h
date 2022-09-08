#pragma once
#include <graphics.h>
#include <iostream>
using namespace std;
class Line
{
private:
	int x_s, y_s, x_e, y_e, x, y;
	double k, b;
	int width;
	COLORREF color;
	double step;

public:
	Line(double XS,double YS,double XE, double YE, double W, COLORREF C,int S) {
		x_s = XS;
		x_e = XE;
		y_s = YS;
		y_e = YE;
		width = W;
		color = C;
		step = S;
		x = XS;
		y = YS;
		k = (y_e-y_s)*1.0 /( x_e - x_s)*1.0;
		b = y_s - k * x_s;
			
	}
	void DrawLine() {
		while (x <= x_e && y <= y_e) {
			//double temp_b = b;
			for (double i = b - width / 2; i < b + width / 2; i += step) {
				putpixel((int)x, y, color);
				y = k * x + i;

			}
			cout << "(" << x << " , " << y << "),k= "<<k<<" ,b= "<<b<<" color= " << color << endl;
			x += step;
		}
	}
	void Bresenham() {
		int dx = abs(x_e - x_s), sx = x_s < x_e ? 1 : -1;
		int dy = abs(y_e - y_s), sy = y_s < y_e ? 1 : -1;
		int err = (dx < dy ? dx : -dy) / 2, e2;
		while (true)
		{
			putpixel(x, y,color);
			if (x == x_e) break;
			e2 = err;
			if (e2 > -dx) {
				err -= dy;
				x += sx;
			}
			if (e2 < dy) {
				err += dx;
				y += sy;
			}
			cout << "(" << x << " , " << y << "),k= " << k << " ,b= " << b << " color= " << color << endl;

		}
	}
	void MidPoint() {
		if (k >= 1) {
			for (y= y_s; y < y_e; y += 1) {
				putpixel(x, y, color);
				cout << "(" << x << " , " << y << "),k= " << k << " ,b= " << b << " color= " << color << endl;

				if ((y + 1) - k * (x + 0.5) - b > 0) {
					x += 1;
				}
			}
		}
		else if (k >= 0) {
			for (x = x_s; x < x_e; x += 1) {
				putpixel(x, y, color);
				cout << "(" << x << " , " << y << "),k= " << k << " ,b= " << b << " color= " << color << endl;

				if ((y + 0.5) - k * (x + 1) - b < 0) {
					y += 1;
				}
			}
		}

	}
};

