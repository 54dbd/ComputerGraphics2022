#include "Line.h"
#include "Starts.h"
#include <iostream>
void showMenu() {
	cout << "|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|                 2022计算机图形学                  |"
		<< "\n|                                                   |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|       A.直线                                |"
		<< "\n|       Z.星轨                                      |"
		<< "\n|       0.退出                                      |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< endl;
}
int main() {
	showMenu();
	char choice;
	
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
		case 'A':
		case 'a':
			initgraph(640, 480);		//初始化窗口大小
			Lines();
			closegraph();
			system("cls");

			showMenu();
			break;
		case'Z':
		case'z':
			initgraph(640, 480);		//初始化窗口大小
			Stars();
			closegraph();
			system("cls");
			showMenu();
			break;
		case'0':
			return 0;
		default:
			break;
		}
	}

	return 0;
}