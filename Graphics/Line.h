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
		if (dx < 2)sx = 0;
		if (dy < 2)sy = 0;
		while (true)
		{

			drawPixel(x, y);
			if (sx == 0)
			{
				if (y == y_e)
					break;
			}
			else if (x == x_e) break;
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
	void Bresenham_textbook() {
		drawPixel(x_s, y_s);
		bool vertical = false, horizontal = false, diagonal = false;
		Translate(vertical, horizontal, diagonal);

		int dx = x_e - x_s;
		int dy = y_e - y_s;
		int increase_E = 2 * dy;
		int increase_NE = 2 * (dy - dx);
		int x = x_s;
		int y = y_s;
		int d = 2 * dy - dx;

		for (x = x_s + 1; x <= x_e; ++x) {
			if (d < 0) {
				d += increase_E;
			}
			else {
				d += increase_NE;
				y++;
			}

			int temp_x = x, temp_y = y;
			Restore(vertical, horizontal, diagonal, temp_x, temp_y);
			drawPixel(temp_x, temp_y);
		}
	}


	void MidPoint() {
		drawPixel(x_s, y_s); // ���Ƴ�ʼ��

		bool vertical = false, horizontal = false, diagonal = false;
		Translate(vertical, horizontal, diagonal);
		int a = y_s - y_e, b = x_e - x_s;
		int d = a + a + b; // d:��ʼ����
		int d1 = a + a, d2 = a + a + b + b; // d1:�������� d2:����������
		int x = x_s, y = y_s; // ��ǰ���Ƶ�
		for (x = x + 1; x <= x_e; ++x) {
			if (d < 0) {
				d += d2;
				y++;
			}
			else {
				d += d1;
			}
			int temp_x = x, temp_y = y;
			Restore(vertical, horizontal, diagonal, temp_x, temp_y);
			drawPixel(temp_x, temp_y);
		}
	}

	void Translate(bool& vertical, bool& horizontal, bool& diagonal) {
		if (y_e - y_s < 0) {
			y_s = -y_s;
			y_e = -y_e;
			vertical = true;
		}
		if (x_e - x_s < 0) {
			x_s = -x_s;
			x_e = -x_e;
			horizontal = true;
		}
		if (y_e - y_s > x_e - x_s) {
			int temp = y_s; y_s = x_s; x_s = temp;
			temp = y_e; y_e = x_e; x_e = temp;
			diagonal = true;
		}
	}

	void Restore(bool& vertical, bool& horizontal, bool& diagonal, int& x, int& y) {
		int temp;
		if (diagonal) { temp = y; y = x; x = temp; }
		if (horizontal) x = -x;
		if (vertical) y = -y;
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
			Line l(X1, Y1, m.x, m.y, -7, WHITE);
			//l.drawPixel(m.x, m.y);
			l.Bresenham();
			// ����������,��ס�յ㲢����
			break;
		}
		if (m.vkcode == VK_NUMPAD0) return;
	}
}