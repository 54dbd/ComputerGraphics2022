#include "configwindow.h"
#include "ui_configwindow.h"

configWindow::configWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configWindow)
{
    ui->setupUi(this);
}

configWindow::~configWindow()
{
    delete ui;
}

void configWindow::on_horizontalSlider_2_valueChanged(int KDKS)
{
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

