#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;
class circle
{
private:
	int cx, cy, r;
	COLORREF color;

	void CirclePoint(int x, int y) {
		putpixel(x + cx, y + cy, color);
		putpixel(y + cx, x + cy, color);
		putpixel(-x + cx, y + cy, color);
		putpixel(y + cx, -x + cy, color);
		putpixel(x + cx, -y + cy, color);
		putpixel(-y + cx, x + cy, color);
		putpixel(-x + cx, -y + cy, color);
		putpixel(-y + cx, -x + cy, color);


	}

public:
	circle(int X = 0, int Y = 0, int R = 0) {
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



};

void Circle() {
	ExMessage m;		//��ȡ����������
	int X1, Y1, X2, Y2, R,flag = 0;
    class circle c;
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:	//����������
			// ��ס���
			flag = 1;
			X1 = m.x;
			Y1 = m.y;
			c.SetCenter(X1, Y1);
			cout << "start:(" << m.x << " , " << m.y << ")" << endl;
			break;

		case WM_LBUTTONUP:		//̧��������
			X2 = m.x;
			Y2 = m.y;
			R = sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
			c.SetR(R);
			c.DrawCircle();
			// ����������,��ס�յ㲢����
			break;
		
		}

		if (m.vkcode == VK_NUMPAD0) return;
	}
}

#endif
