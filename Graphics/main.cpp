#include "Line.h"
#include "Starts.h"
#include "Circle.h"
#include "Arc.h"
#include <iostream>
void showMenu() {
	cout << "|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|                 2022¼ÆËã»úÍ¼ÐÎÑ§                  |"
		<< "\n|                                                   |"
		<< "\n|                                                   |"
		<< "\n|***************************************************|"
		<< "\n|                                                   |"
		<< "\n|       A.Ö±Ïß                                      |"
		<< "\n|       B.Ô²                                        |"
		<< "\n|       C.ÈÎÒâÔ²»¡                                  |"
		<< "\n|       Z.ÐÇ¹ì                                      |"
		<< "\n|       0.ÍË³ö                                      |"
		<< "\n|       1.ÉèÖÃ                                      |"
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
			initgraph(640, 480);		//³õÊ¼»¯´°¿Ú´óÐ¡
			Lines(brushType,colorType);
			closegraph();
			system("cls");

			/*showMenu();*/
			break;
		case 'B':
		case 'b':
			initgraph(640, 640);		//³õÊ¼»¯´°¿Ú´óÐ¡
			Circles(brushType, colorType);

			closegraph();
			system("cls");

			//showMenu();
			break;
		case 'C':
		case 'c':
			initgraph(640, 640);		//³õÊ¼»¯´°¿Ú´óÐ¡
			Anyarc(brushType, colorType);

			closegraph();
			system("cls");

			//showMenu();
			break;
		case'Z':
		case'z':
			initgraph(640, 480);		//³õÊ¼»¯´°¿Ú´óÐ¡
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
			cout << "±ÊË¢1£ºµ¥ÏñËØ±ÊË¢"
				<< "\n±ÊË¢2£º3ÏñËØX±ÊË¢"
				<< "\n±ÊË¢3£º5ÏñËØX±ÊË¢"
				<< "\n±ÊË¢4£º7ÏñËØX±ÊË¢"
				<< "\n±ÊË¢5£º7ÏñËØO±ÊË¢"
				<< "\n±ÊË¢6£º9ÏñËØ¿Ú±ÊË¢"
				<< endl;
			cout << "ÇëÑ¡Ôñ±ÊË¢ÀàÐÍ£º";
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
			cout << "ÑÕÉ«1£ººÚ"
				<< "\nÑÕÉ«2£ºÀ¶"
				<< "\nÑÕÉ«3£ºÂÌ"
				<< "\nÑÕÉ«4£ºÇà"
				<< "\nÑÕÉ«5£ººì"
				<< "\nÑÕÉ«6£º×Ï"
				<< "\nÑÕÉ«7£º×Ø"
				<< "\nÑÕÉ«8£ºÇ³»Ò"
				<< "\nÑÕÉ«9£ºÉî»Ò"
				<< "\nÑÕÉ«a£ºÁÁÀ¶"
				<< "\nÑÕÉ«b£ºÁÁÂÌ"
				<< "\nÑÕÉ«c£ºÁÁÇà"
				<< "\nÑÕÉ«d£ºÁÁºì"
				<< "\nÑÕÉ«e£ºÁÁ×Ï"
				<< "\nÑÕÉ«f£º»Æ"
				<< "\nÑÕÉ«g£º°×"
				<< endl;
			cout << "ÇëÑ¡Ôñ±ÊË¢ÀàÐÍ£º";
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