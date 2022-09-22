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
		//���浱ǰ��ɫ
		COLORREF temp = getColor();
		//ʹ�ú�ɫ����켣
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
		//�ָ���ɫ
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
			//���ߴ���
			if (ct % 31 > 15) {
				CirclePoint(x, y);
			}
			ct++;
		}

	}

};

void Circles(int brushType, COLORREF colorType) {
	ExMessage m;		//��ȡ����������
	int X1, Y1, X2, Y2, R,flag = 0;
	//����Բ������
     Circle c(0,0,0, brushType, colorType);
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

		if (m.vkcode == VK_ESCAPE) break;
	}
}

#endif
