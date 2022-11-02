#include "configwindow.h"
#include "ui_configwindow.h"

configWindow::configWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configWindow)
{
    this->setGeometry(0,0,400,166);
    ui->setupUi(this);
}

configWindow::~configWindow()
{
    delete ui;
}

void configWindow::on_horizontalSlider_2_valueChanged(int KDKS)
{
    //因为滑动条输入都是整数，这里将其转为小数。
    kdks = KDKS/100.0;
    QString output = QString::number(kdks);
    ui->kdks->setText(output);
    emit sendValue(n, kdks);
}


void configWindow::on_horizontalSlider_valueChanged(int N)
{
    n = N;
    QString output = QString::number(n);
    ui->n->setText(output);
    emit sendValue(n, kdks);
}

