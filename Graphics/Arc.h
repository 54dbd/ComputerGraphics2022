#ifndef __Arc_H__
#define __Arc_H__
#include <graphics.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <socketapi.h>



#define PUTPIXELX(x,y,boder1,boder2,colour)               if(x>=boder1&&x<=boder2)  \
                                                              putpixel(x,y,colour);



#define PUTPIXELY(x,y,boder1,boder2,colour)                 if(y>=boder1&&y<=boder2)  \
                                                              putpixel(x, y, colour);


class Arc
{
private:
	int cx, cy, r;
	COLORREF color;


	void ArcPointX(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {

		PUTPIXELX(x + cx, y + cy, Borderup, Borderup2, color);
		PUTPIXELX(y + cx, x + cy, Borderup, Borderup2, color);
		PUTPIXELX(-x + cx, y + cy, Borderup, Borderup2, color);
		PUTPIXELX(y + cx, -x + cy, Borderdown, Borderdown2, color);
		PUTPIXELX(x + cx, -y + cy, Borderdown, Borderdown2, color);
		PUTPIXELX(-y + cx, x + cy, Borderup, Borderup2, color);
		PUTPIXELX(-x + cx, -y + cy, Borderdown, Borderdown2, color);
		PUTPIXELX(-y + cx, -x + cy, Borderdown, Borderdown2, color);


	}

	void ArcPointY(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {

		PUTPIXELY(x + cx, y + cy, Borderup, Borderup2, color);
		PUTPIXELY(y + cx, x + cy, Borderup, Borderup2, color);
		PUTPIXELY(-x + cx, y + cy, Borderdown, Borderdown2, color);
		PUTPIXELY(y + cx, -x + cy, Borderup, Borderup2, color);
		PUTPIXELY(x + cx, -y + cy, Borderup, Borderup2, color);
		PUTPIXELY(-y + cx, x + cy, Borderdown, Borderdown2, color);
		PUTPIXELY(-x + cx, -y + cy, Borderdown, Borderdown2, color);
		PUTPIXELY(-y + cx, -x + cy, Borderdown, Borderdown2, color);


	}
	void ArcPointN(int x, int y, int Borderup, int Borderup2, int Borderdown, int Borderdown2) {
		if ((Borderdown - cx) < 0) {
			PUTPIXELY(-x + cx, y + cy, Borderup, Borderup2, color);
			PUTPIXELY(-y + cx, x + cy, Borderup, Borderup2, color);
			PUTPIXELY(-x + cx, -y + cy, Borderup, Borderup2, color);
			PUTPIXELY(-y + cx, -x + cy, Borderup, Borderup2, color);
		}
		else {
			PUTPIXELY(x + cx, y + cy, Borderup, Borderup2, color);
			PUTPIXELY(y + cx, x + cy, Borderup, Borderup2, color);
			PUTPIXELY(y + cx, -x + cy, Borderup, Borderup2, color);
			PUTPIXELY(x + cx, -y + cy, Borderup, Borderup2, color);
		}

	}

	//��Բ����Խx����������ʼ����Ԥ����
	void ConfigX(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2) {
		if (x2 < (2 * cx - x1)) {    //˵��ԭ�������Ҳ࣬���Ӧ�ӻ����������Ϊ -r
			Borderup = cx - r;
			Borderdown = cx - r;
			if ((y2 - cy) > 0) {        //��ʱy1��y2����һ��λ��x���Ϸ��������y2���Ϸ��������Բ����x���Ϸ��Ĳ��֣����ҽ�Ϊx2,�·��Ĳ����ҽ�Ϊx1
				Borderup2 = x2;
				Borderdown2 = x1;
			}
			else {
				Borderup2 = x1;
				Borderdown2 = x2;
			}
		}
		else {                         //����������෴
			Borderup2 = cx + r;
			Borderdown2 = cx + r;
			if ((y2 - cy) > 0) {
				Borderup = x2;
				Borderdown = x1;
			}
			else {
				Borderup = x1;
				Borderdown = x2;
			}
		}
	}
	//��Բ����Խy����������ʼ����Ԥ���������߼���ConfigXһ��
	void ConfigY(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2) {
		if (y2 < (2 * cy - y1)) {
			Borderup = cy - r;
			Borderdown = cy - r;
			if ((x2 - cx) > 0) {
				Borderup2 = y2;
				Borderdown2 = y1;
			}
			else {
				Borderup2 = y1;
				Borderdown2 = y2;
			}
		}
		else {
			Borderup2 = cy + r;
			Borderdown2 = cy + r;
			if ((x2 - cx) > 0) {
				Borderup = y2;
				Borderdown = y1;
			}
			else {
				Borderup = y1;
				Borderdown = y2;
			}
		}
	}


	//��������Ԥ������
	void ArcConfig(int x1, int y1, int x2, int y2, int& Borderup, int& Borderup2, int& Borderdown, int& Borderdown2, int& flag) {
		if ((cy - y1) * (cy - y2) < 0) {      //�˴��ж��Ƿ��Խx��
			flag = 1;
			ConfigX(x1, y1, x2, y2, Borderup, Borderup2, Borderdown, Borderdown2); //�Կ�Խx����������Ԥ����
		}
		else if ((cx - x1) * (cx - x2) < 0) {  //�Ƿ��Խy��
			flag = 2;
			ConfigY(x1, y1, x2, y2, Borderup, Borderup2, Borderdown, Borderdown2); //�Կ�Խy����������Ԥ����
		}
		else {                       //Բ��ֻ��һ������
			flag = 0;
			if (y1 < y2) {
				Borderdown = x1;
				Borderup = y1;
				Borderup2 = y2;          //ѡ��y���߽�
			}
			else {
				Borderdown = x1;
				Borderup = y2;
				Borderdown2 = Borderup2 = y1;
			}
		}

	}

public:
	Arc(int X = 0, int Y = 0, int R = 0) {
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


	void DrawArc(int x1, int y1, int x2, int y2) {       //��������Բ������ʵ�ֵĹ��̸������ԣ��ǵ�����һ����ʱ������Ԥ����õ���һ��Բ����������յ����жϸõ㣬�Լ��õ�������7��1/2���޵�ӳ���Ƿ���Բ����
		int x, y, d, e, Borderup, Borderup2, Borderdown1, Borderdown2, flag;         //��һ����Ϊ���������Բ����Խy�ᣬԲ����Խx�ᣬ�򲻿�Խ�κ������ᡣǰ����������ص��Ĳ��֣�������Ӱ��
		ArcConfig(x1, y1, x2, y2, Borderup, Borderup2, Borderdown1, Borderdown2, flag);   //��ʼ���ú������������������������Ҫ�Ľ���                                    
		x = 0;
		y = r;
		e = 1 - r;
		if (flag == 1) {
			while (x <= y) {
				if (e < 0)
					e += 2 * x + 3;
				else {
					e += 2 * (x - y) + 5;
					y--;
				}
				x++;
				ArcPointX(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);

			}
		}
		else if (flag == 2) {
			while (x <= y) {
				if (e < 0)
					e += 2 * x + 3;
				else {
					e += 2 * (x - y) + 5;
					y--;
				}
				x++;
				ArcPointY(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);
			}

		}
		else if (flag == 0) {
			while (x <= y) {
				if (e < 0)
					e += 2 * x + 3;
				else {
					e += 2 * (x - y) + 5;
					y--;
				}
				x++;
				ArcPointN(x, y, Borderup, Borderup2, Borderdown1, Borderdown2);

			}
		}
	}


};



void Anyarc() {
	ExMessage m;		//��ȡ����������
	int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0, R = 0, flag = 0;
	class Arc a;
	while (true) {
		m = getmessage(EM_MOUSE | EM_KEY);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:	//����������
			X1 = m.x;        //��¼Բ��
			Y1 = m.y;        //
			a.SetCenter(X1, Y1);
			while (true) {
				m = getmessage(EM_MOUSE | EM_KEY);
				if (m.message == WM_LBUTTONDOWN) {
					X2 = m.x;                   //��¼Բ����һ����
					Y2 = m.y;
					R = sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
					a.SetR(R);
					//c.DrawCircle();
					while (true) {
						m = getmessage(EM_MOUSE | EM_KEY);
						if (m.message == WM_LBUTTONDOWN) {
							int cx = X1, cy = Y1, x, y;
							X1 = m.x;                   //��¼Բ���ڶ����㣬��һ����һ����Բ�ϣ����ڶ�������һ���������Ҫ��������
							Y1 = m.y;
							x = X1 - cx;
							y = Y1 - cy;
							if (abs(cx - X1) > R) {
								X1 = cx + R * x / abs(x);      //�Գ��������귶Χ��Xȡ���ֵ
							}
							Y1 = cy + sqrt((R * R - (X1 - cx) * (X1 - cx))) * y / abs(y);      //����Yֵ���������Բ�ϵ�ֵ
							a.DrawArc(X2, Y2, X1, Y1);
							break;
						}

					}
					//while(true)
					break;
				}
			}
			break;



		}

		if (m.vkcode == VK_NUMPAD0) return;
	}

}

#endif
#pragma once
