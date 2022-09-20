#pragma once
#include <vector>
using namespace std;
class Brush
{
private:
	vector<vector<int>>const* brush;
	COLORREF color;
public:
	//����ˢ_9
	const vector<vector<int>> brush_9 = {
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
	};
	//Բˢ_7
	const vector<vector<int>> brush_7_r = {
		{0,0,1,1,1,0,0},
		{0,1,1,1,1,1,0},
		{1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1},
		{0,1,1,1,1,1,0},
		{0,0,1,1,1,0,0},

	};
	//Xˢ_7
	const vector<vector<int>> brush_7 = {
		{1,1,0,0,0,0,1},
		{0,1,1,0,0,1,1},
		{0,0,1,1,1,1,0},
		{0,0,0,1,1,0,0},
		{0,0,1,1,1,1,0},
		{0,1,1,0,0,1,1},
		{1,1,0,0,0,0,1},

	};
	//Xˢ_5
	const vector<vector<int>> brush_5 = {
		{1,1,0,0,1},
		{0,1,1,1,1},
		{0,0,1,1,0},
		{0,1,1,1,1},
		{1,1,0,0,1}
	};
	//Xˢ_3
	const vector<vector<int>> brush_3 = {
		{1,0,1},
		{0,1,0},
		{1,0,1}
	};
	//1ˢ
	const vector<vector<int>> brush_1 = {
		{1,},
	};
	Brush(int W, COLORREF C) {

		color = C;
		setBrushType(W);
	};
	Brush() {
		color = WHITE;
		setBrushType(5);
	};
	int setColor(COLORREF C) {
		color = C;
		return 0;
	};
	int setBrushType(int W) {
		switch (W)
		{
		case 1:
			brush = &brush_1;
			break;
		case 3:
			brush = &brush_3;
			break;
		case 5:
			brush = &brush_5;
			break;
		case -7:
			brush = &brush_7_r;
			break;
		case 7:
			brush = &brush_7;
			break;
		case 9:
			brush = &brush_9;
			break;
		default:
			brush = &brush_3;
			break;
		}
		return 1;
	};
	void drawPixel(int x, int y) {
		for (int i = 0; i < (*brush).size(); i++) {
			for (int j = 0; j < (*brush).size(); j++) {
				if ((*brush)[i][j]) putpixel(x + i, y + j, color);

			}
		}
	};
};

