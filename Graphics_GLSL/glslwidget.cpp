#include "glslwidget.h"
#include "ui_glslwidget.h"
#include <QGridLayout>
#include "openglwidget.h"
#include "configwindow.h"

GLSLWidget::GLSLWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GLSLWidget)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout();
    glWidget = new OpenGLWidget(n,kdks);
    layout->addWidget(glWidget);
    setLayout(layout);

    configWindow *window = new configWindow();
    window->show();

    connect(window,SIGNAL(sendValue(int,double)),this,SLOT(getValue(int,double)));

}

GLSLWidget::~GLSLWidget()
{
    delete ui;
}

void GLSLWidget::getValue(int N, double KDKS){
    qDebug()<<N<<KDKS;
    n = N;
    kdks = KDKS;
}
