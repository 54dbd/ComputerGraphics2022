#pragma once
#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <ctime>
#define MAXSTAR 200	// ��������
#define CENTER_X 320
#define CENTER_Y 240
using namespace std;
struct STAR
{
	double	x;
	double	y;
	double radius;
	double angle;
	double	step;
	int		color;
};

STAR star[MAXSTAR];

// ��ʼ������
void InitStar(int i)
{
	star[i].x = rand() % 320;
	star[i].y = 240;
	star[i].radius = 320 - star[i].x;

	star[i].step = ((rand() % 5000) / 100000.0);
	//star[i].step = 0.01;
	star[i].color = (int)(star[i].step * 255 / 0.05);	// �ٶ�Խ�죬��ɫԽ��
	//star[i].color = 255;
	star[i].color = RGB((rand() % 100 / 100.0) * star[i].color, (rand() % 100 / 100.0) * star[i].color, (rand() % 100 / 100.0) * star[i].color);
}

// �ƶ�����
void MoveStar(int i, ExMessage& m, double rotate)
{
	// ����ԭ��������
	//putpixel((int)star[i].x, star[i].y, 0);

	double X = CENTER_X;
	double Y = CENTER_Y;

	X = m.x;
	Y = m.y;
	std::cout << rotate << std::endl;
	// ������λ��
	star[i].angle += star[i].step;
	star[i].y = star[i].radius * sin(star[i].angle + rotate) + Y;
	star[i].x = star[i].radius * cos(star[i].angle + 100) * -1 + X;

	// ��������
	putpixel((int)star[i].x, star[i].y, star[i].color);
}



void Stars(void)
{
	srand((unsigned)time(NULL));	// �������
	initgraph(640, 480);			// ������ͼ����

	// ��ʼ����������
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}

	// �����ǿգ���������˳�
	ExMessage m;		// ������Ϣ����
	double rotate = 0;
	while (!_kbhit())
	{

		for (int i = 0; i < MAXSTAR; i++)
		{
			peekmessage(&m, EM_MOUSE | EM_KEY);
			if (m.vkcode == VK_NUMPAD0) return;
			if (m.lbutton) {
				rotate += 0.001;
				cleardevice();
			}
			else if (m.rbutton) {
				rotate -= 0.001;
				cleardevice();
			}
			MoveStar(i, m, rotate);
		}
		//Sleep(10);
	}
}
