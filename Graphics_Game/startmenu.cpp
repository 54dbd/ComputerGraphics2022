#include "startmenu.h"
#include "ui_startmenu.h"
#include "mypaint.h"
#include <QPixmap>

startMenu::startMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startMenu)
{
    this->setGeometry(350, 200, 600, 400);//设置窗体大小、位置
    this->setFixedSize(600, 400);

    ui->setupUi(this);
}

startMenu::~startMenu()
{
    delete ui;
}

void startMenu::on_pushButton_2_clicked()
{
    close();
}


void startMenu::on_pushButton_clicked()
{
    MyPaint *w = new MyPaint();
    w->setWindowIcon(QIcon(":/png/images/1.png"));
    w->show();
    close();
}

