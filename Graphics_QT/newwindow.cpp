#include "newwindow.h"
#include "ui_newwindow.h"
#include <QPen>
newWindow::newWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newWindow)
{
    ui->setupUi(this);
}

newWindow::~newWindow()
{
    delete ui;
}

void newWindow::on_pushButton_clicked()
{
    close();
}
void newWindow::getPen(QPen* p){
    pen = p;
    qDebug()<<"setting pen";
}


void newWindow::on_horizontalSlider_sliderMoved(int position)//position: 1~20
{
    _width = position;
    QString output = QString::number(position)+"px";
    ui->width->setText(output);
    (*pen).setWidth(_width);
}


void newWindow::on_red_clicked()
{
    _color = Qt::red;
    (*pen).setColor(_color);
}


void newWindow::on_blue_clicked()
{
    _color = Qt::blue;
    (*pen).setColor(_color);
}


void newWindow::on_yellow_clicked()
{
    _color = Qt::yellow;
    (*pen).setColor(_color);
}


void newWindow::on_green_clicked()
{
    _color = Qt::green;
    (*pen).setColor(_color);
}


void newWindow::on_black_clicked()
{
    _color = Qt::black;
    (*pen).setColor(_color);
}


void newWindow::on_horizontalSlider_actionTriggered(int action)
{

}


void newWindow::on_horizontalSlider_sliderPressed()
{

}


void newWindow::on_horizontalSlider_valueChanged(int value)
{
    _width = value;
    QString output = QString::number(value)+"px";
    ui->width->setText(output);
    (*pen).setWidth(_width);

}


void newWindow::on_dashLine_stateChanged(int arg1)
{
    qDebug()<<arg1<<(*pen).style();
    if(arg1){
        _style = Qt::DashLine;

    }else{
        _style = Qt::SolidLine;
    }
    (*pen).setStyle(_style);

}

