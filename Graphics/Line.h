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
			for (int i = -width / 2; i < width / 2; i++)
			{
				putpixel(x+i, y+i, color);
			}
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

			//cout << "(" << x << " , " << y << "),k= " << k << " ,b= " << b << " color= " << color << endl;

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
	void Midpointline()
	{
		int a, b, d1, d2, x, y,d;
		a = y_s - y_e; 
		b = x_e - x_s;  
		d = a + a + b;  //计算a,b,d0
		d1 = a + a;  
		d2 = a + a + b + b;            //计算可能的增量
		x = x_s; 
		y = y_s;
		putpixel(x, y, color);
		while (x != x_e&&y!=y_e)
		{

			if (d < 0)
			{
				x++;
				y++;
				d += d2;
			}  //如果d为负，取右上角点(y加1)
			else {
				x++;
				d += d1;
			}          //如果d为正，取右边点
			
			
			putpixel(x, y, color);
		}
	}
};

void Lines() {
	ExMessage m;		//获取鼠标操作对象
	int X1, Y1;
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:	//按下鼠标左键
			// 记住起点
			X1 = m.x;
			Y1 = m.y;
			cout << "start:(" << m.x << " , " << m.y << ")" << endl;
			break;

		case WM_LBUTTONUP:		//抬起鼠标左键
			if ((m.x - X1) * (m.x - X1) + (m.y - Y1) * (m.y - Y1) < 10)
			{
				cout << "Too short!" << endl;
				break;
			}
			cout << "end:(" << m.x << " , " << m.y << ")" << endl;
			Line l(X1, Y1, m.x, m.y, 10, WHITE, 1);
			l.Bresenham();
			// 鼠标左键弹起,记住终点并画线
			break;
		}
		if (m.vkcode == VK_NUMPAD0) return;
	}
}