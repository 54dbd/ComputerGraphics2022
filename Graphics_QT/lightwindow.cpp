#include "lightwindow.h"
#include "ui_lightwindow.h"

lightWindow::lightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lightWindow)
{
    ui->setupUi(this);
}

lightWindow::~lightWindow()
{
    delete ui;
}
