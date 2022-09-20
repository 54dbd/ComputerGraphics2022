#include "mainwindow.h"
#include "Line.h"
#include "Starts.h"
#include "Circle.h"
#include <QApplication>
#include <iostream>
void showMenu() {
    cout << "|***************************************************|"
        << "\n|                                                   |"
        << "\n|                 2022计算机图形学                  |"
        << "\n|                                                   |"
        << "\n|                                                   |"
        << "\n|***************************************************|"
        << "\n|                                                   |"
        << "\n|       A.直线                                      |"
        << "\n|       B.圆弧                                      |"
        << "\n|       Z.星轨                                      |"
        << "\n|       0.退出                                      |"
        << "\n|                                                   |"
        << "\n|***************************************************|"
        << endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

