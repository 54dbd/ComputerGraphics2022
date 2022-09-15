#pragma once
#include <graphics.h>
#include <iostream>
#include "Brush.h"
using namespace std;
class Line : public Brush
{
	
private:
	int x_s, y_s, x_e, y_e, x, y;
	int width;

public:
	Line(int XS, int YS, int XE, int YE, int W, COLORREF C):Brush(W,C) {
		x_s = XS;
		x_e = XE;
		y_s = YS;
		y_e = YE;
		width = W;
		x = XS;
		y = YS;

	}
	void Bresenham() {
		int dx = abs(x_e - x_s), sx = x_s < x_e ? 1 : -1;
		int dy = abs(y_e - y_s), sy = y_s < y_e ? 1 : -1;
		int err = (dx < dy ? dx : -dy) / 2, e2;
		while (true)
		{

			drawPixle(x ,y);

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
		//TODO:���Ҳ���
	}
	void Midpointline()
	{
		int a, b, d1, d2, x, y,d;
		a = y_s - y_e; 
		b = x_e - x_s;  
		d = a + a + b;  //����a,b,d0
		d1 = a + a;  
		d2 = a + a + b + b;            //������ܵ�����
		x = x_s; 
		y = y_s;
		drawPixle(x, y);
		while (x != x_e&&y!=y_e)
		{

			if (d < 0)
			{
				x++;
				y++;
				d += d2;
			}  //���dΪ����ȡ���Ͻǵ�(y��1)
			else {
				x++;
				d += d1;
			}          //���dΪ����ȡ�ұߵ�
			
			
			drawPixle(x, y);
		}
	}
	
};

void Lines() {
	ExMessage m;		//��ȡ����������
	int X1, Y1;
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:	//����������
			// ��ס���
			X1 = m.x;
			Y1 = m.y;
			cout << "start:(" << m.x << " , " << m.y << ")" << endl;
			break;

		case WM_LBUTTONUP:		//̧��������
			if ((m.x - X1) * (m.x - X1) + (m.y - Y1) * (m.y - Y1) < 10)
			{
				cout << "Too short!" << endl;
				break;
			}
			cout << "end:(" << m.x << " , " << m.y << ")" << endl;
			Line l(X1, Y1, m.x, m.y, 9, WHITE);
			//l.drawPixle(m.x, m.y);
			l.Bresenham();
			// ����������,��ס�յ㲢����
			break;
		}
		if (m.vkcode == VK_NUMPAD0) return;
	}
}