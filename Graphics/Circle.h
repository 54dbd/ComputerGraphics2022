#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;



class Circle : public Brush
{
private:
	int cx, cy, r;
	COLORREF color;

	void CirclePoint(int x, int y) {
		drawPixel(x + cx, y + cy);
		drawPixel(y + cx, x + cy);
		drawPixel(-x + cx, y + cy);
		drawPixel(y + cx, -x + cy);
		drawPixel(x + cx, -y + cy);
		drawPixel(-y + cx, x + cy);
		drawPixel(-x + cx, -y + cy);
		drawPixel(-y + cx, -x + cy);


	}

public:
	Circle(int X = 0, int Y = 0, int R = 0,int W=3, COLORREF C = WHITE):Brush(W,C) {
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

	void Clear() {
		int x, y, d, e;
		//缓存当前颜色
		COLORREF temp = getColor();
		//使用黑色清除轨迹
		setColor(BLACK);
		x = 0;
		y = r;
		e = 1 - r;
		CirclePoint(x, y);
		while (x <= y) {
			if (e < 0)
				e += 2 * x + 3;
			else {
				e += 2 * (x - y) + 5;
				y--;
			}
			x++;
			CirclePoint(x, y);
		}
		//恢复颜色
		setColor(temp);
	}
	void DrawCircle() {
		int x, y, d, e;
		x = 0;
		y = r;
		e = 1 - r;
		CirclePoint(x, y);
		while (x <= y) {
			if (e < 0)
				e += 2 * x + 3;
			else {
				e += 2 * (x - y) + 5;
				y--;
			}
			x++;
			CirclePoint(x,y);
		}

	}

	void DrawDashLIneCircle() {
		int x, y, d, e,ct=0;
		x = 0;
		y = r;
		e = 1 - r;
		CirclePoint(x, y);
		while (x <= y) {
			if (e < 0)
				e += 2 * x + 3;
			else {
				e += 2 * (x - y) + 5;
				y--;
			}
			x++;
			//虚线处理
			if (ct % 31 > 15) {
				CirclePoint(x, y);
			}
			ct++;
		}

	}

};

void Circles(int brushType, COLORREF colorType) {
	ExMessage m;		//获取鼠标操作对象
	int X1, Y1, X2, Y2, R,flag = 0;
	//设置圆的属性
     Circle c(0,0,0, brushType, colorType);
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:	//按下鼠标左键
			// 记住起点
			flag = 1;
			X1 = m.x;
			Y1 = m.y;
			c.SetCenter(X1, Y1);
			cout << "start:(" << m.x << " , " << m.y << ")" << endl;
			break;

		case WM_LBUTTONUP:		//抬起鼠标左键
			X2 = m.x;
			Y2 = m.y;
			R = sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
			c.SetR(R);
			c.DrawCircle();
			// 鼠标左键弹起,记住终点并画线
			break;
		
		}

		if (m.vkcode == VK_NUMPAD0) return;
	}
}

#endif
