#pragma once
#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <ctime>
#define MAXSTAR 200	// 星星总数
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

// 初始化星星
void InitStar(int i)
{
	star[i].x = rand() % 320;
	star[i].y = 240;
	star[i].radius = 320 - star[i].x;

	star[i].step = ((rand() % 5000) / 100000.0);
	//star[i].step = 0.01;
	star[i].color = (int)(star[i].step * 255 / 0.05);	// 速度越快，颜色越亮
	//star[i].color = 255;
	star[i].color = RGB((rand() % 100 / 100.0) * star[i].color, (rand() % 100 / 100.0) * star[i].color, (rand() % 100 / 100.0) * star[i].color);
}

// 移动星星
void MoveStar(int i, ExMessage& m, double rotate)
{
	// 擦掉原来的星星
	//putpixel((int)star[i].x, star[i].y, 0);

	double X = CENTER_X;
	double Y = CENTER_Y;

	X = m.x;
	Y = m.y;
	std::cout << rotate << std::endl;
	// 计算新位置
	star[i].angle += star[i].step;
	star[i].y = star[i].radius * sin(star[i].angle + rotate) + Y;
	star[i].x = star[i].radius * cos(star[i].angle + 100) * -1 + X;

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
}



void Stars(void)
{
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(640, 480);			// 创建绘图窗口

	// 初始化所有星星
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}

	// 绘制星空，按任意键退出
	ExMessage m;		// 定义消息变量
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
