#include "Line.h"
#include "Starts.h"
#include <iostream>
void showMenu() {
	cout << "|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|                 2022�����ͼ��ѧ                  |"
		<< "\n|                                                   |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|       A.ֱ��                                |"
		<< "\n|       Z.�ǹ�                                      |"
		<< "\n|       0.�˳�                                      |"
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
			initgraph(640, 480);		//��ʼ�����ڴ�С
			Lines();
			closegraph();
			system("cls");

			showMenu();
			break;
		case'Z':
		case'z':
			initgraph(640, 480);		//��ʼ�����ڴ�С
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