#include <QApplication>
#include "mypaint.h"
#include "startmenu.h"



int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    startMenu *w = new startMenu();
    w->setWindowIcon(QIcon(":/png/images/1.png"));
    w->show();
    return app.exec();
}
