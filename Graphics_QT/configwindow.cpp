#include "configwindow.h"
#include "ui_configwindow.h"
#include <QPen>
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

void configWindow::on_pushButton_clicked()
{
    close();
}
void configWindow::getPen(settings p){
    pen = p.pen;
    kValue=p.kValue;
    qDebug()<<"setting pen";
}

void configWindow::on_horizontalSlider_sliderMoved(int position)//position: 1~20
{
    _width = position;
    QString output = QString::number(position)+"px";
    ui->width->setText(output);
    (*pen).setWidth(_width);
}


void configWindow::on_red_clicked()
{
    _color = Qt::red;
    (*pen).setColor(_color);
}


void configWindow::on_blue_clicked()
{
    _color = Qt::blue;
    (*pen).setColor(_color);
}


void configWindow::on_yellow_clicked()
{
    _color = Qt::yellow;
    (*pen).setColor(_color);
}


void configWindow::on_green_clicked()
{
    _color = Qt::green;
    (*pen).setColor(_color);
}


void configWindow::on_black_clicked()
{
    _color = Qt::black;
    (*pen).setColor(_color);
}


void configWindow::on_horizontalSlider_actionTriggered(int action)
{

}


void configWindow::on_horizontalSlider_sliderPressed()
{

}


void configWindow::on_horizontalSlider_valueChanged(int value)
{
    _width = value;
    QString output = QString::number(value)+"px";
    ui->width->setText(output);
    (*pen).setWidth(_width);

}


void configWindow::on_dashLine_stateChanged(int arg1)
{
    qDebug()<<arg1<<(*pen).style();
    if(arg1){
        emit sendStyle(Qt::DashLine);
        _style = Qt::DashLine;

    }else{
        emit sendStyle(Qt::DashLine);
        _style = Qt::SolidLine;
    }
    (*pen).setStyle(_style);
    qDebug()<<"penIsSolid:"<<(*pen).style();

}


void configWindow::on_horizontalSlider_2_rangeChanged(int min, int max)
{

}


void configWindow::on_horizontalSlider_2_sliderMoved(int value)
{
    QString output = QString::number(value);
    ui->kValue->setText(output);
    qDebug()<<"[config]kValue:"<<value;
    *kValue=value;

}

