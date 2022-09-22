#include "Line.h"
#include "Starts.h"
#include "Circle.h"
#include "Arc.h"
#include <iostream>
void showMenu() {
	cout << "|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|                 2022�����ͼ��ѧ                  |"
		<< "\n|                                                   |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|       A.ֱ��                                      |"
		<< "\n|       B.Բ                                        |"
		<< "\n|       C.����Բ��                                  |"
		<< "\n|       Z.�ǹ�                                      |"
		<< "\n|       0.�˳�                                      |"
		<< "\n|       1.����                                      |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< endl;
}
int main() {
	//showMenu();
	char choice,brushChoice,colorChoice;
	int brushType=1;
	COLORREF colorType = WHITE;
	while (true)
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case 'A':
		case 'a':
			initgraph(640, 480);		//��ʼ�����ڴ�С
			Lines(brushType,colorType);
			closegraph();
			system("cls");

			/*showMenu();*/
			break;
		case 'B':
		case 'b':
			initgraph(640, 640);		//��ʼ�����ڴ�С
			Circles(brushType, colorType);

			closegraph();
			system("cls");

			//showMenu();
			break;
		case 'C':
		case 'c':
			initgraph(640, 640);		//��ʼ�����ڴ�С
			Anyarc(brushType, colorType);

			closegraph();
			system("cls");

			//showMenu();
			break;
		case'Z':
		case'z':
			initgraph(640, 480);		//��ʼ�����ڴ�С
			Stars();
			closegraph();
			system("cls");
			//showMenu();
			break;
		case'0':
			return 0;
			break;
		case'1':
			
			system("cls");
			cout << "��ˢ1�������ر�ˢ"
				<< "\n��ˢ2��3����X��ˢ"
				<< "\n��ˢ3��5����X��ˢ"
				<< "\n��ˢ4��7����X��ˢ"
				<< "\n��ˢ5��7����O��ˢ"
				<< "\n��ˢ6��9���ؿڱ�ˢ"
				<< endl;
			cout << "��ѡ���ˢ���ͣ�";
			cin >> brushChoice;
			switch (brushChoice)
			{
			case'1':
				brushType = 1;
				break;
			case'2':
				brushType = 3;
				break;
			case'3':
				brushType = 5;
				break;
			case'4':
				brushType = 7;
				break;
			case'5':
				brushType = -7;
				break;
			case'6':
				brushType = 9;
				break;
			default:
				brushType = 1;
				break;
			}
			system("cls");
			cout << "��ɫ1����"
				<< "\n��ɫ2����"
				<< "\n��ɫ3����"
				<< "\n��ɫ4����"
				<< "\n��ɫ5����"
				<< "\n��ɫ6����"
				<< "\n��ɫ7����"
				<< "\n��ɫ8��ǳ��"
				<< "\n��ɫ9�����"
				<< "\n��ɫa������"
				<< "\n��ɫb������"
				<< "\n��ɫc������"
				<< "\n��ɫd������"
				<< "\n��ɫe������"
				<< "\n��ɫf����"
				<< "\n��ɫg����"
				<< endl;
			cout << "��ѡ���ˢ���ͣ�";
			cin >> colorChoice;
			switch (colorChoice)
			{
			case'1':
				colorType = BLACK;
				break;
			case'2':
				colorType = BLUE;
				break;
			case'3':
				colorType = GREEN;
				break;
			case'4':
				colorType = CYAN;
				break;
			case'5':
				colorType = RED;
				break;
			case'6':
				colorType = MAGENTA;
				break;
			case'7':
				colorType = BROWN;
				break;
			case'8':
				colorType = LIGHTGRAY;
				break;
			case'9':
				colorType = DARKGRAY;
				break;
			case'a':
				colorType = LIGHTBLUE;
				break;
			case'b':
				colorType = LIGHTGREEN;
				break;
			case'c':
				colorType = LIGHTCYAN;
				break;
			case'd':
				colorType = LIGHTRED;
				break;
			case'e':
				colorType = LIGHTMAGENTA;
				break;
			case'f':
				colorType = YELLOW;
				break;
			case'g':
				colorType = WHITE;
				break;
			default:
				brushType = WHITE;
				break;
			}
			system("cls");

			//showMenu();
			break;
		default:
			break;
		}
	}

	return 0;
}