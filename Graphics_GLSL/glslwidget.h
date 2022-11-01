#ifndef GLSLWIDGET_H
#define GLSLWIDGET_H

#include <QWidget>


class OpenGLWidget;
namespace Ui {
class GLSLWidget;
}

class GLSLWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GLSLWidget(QWidget *parent = 0);
    ~GLSLWidget();

private:
    Ui::GLSLWidget *ui;
    OpenGLWidget *glWidget;
    int n = 100;
    double kdks = 0.25;

public slots:
    void getValue(int k, double kdks);
};

#endif // GLSLWIDGET_H
