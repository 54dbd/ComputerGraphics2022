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
};

#endif // GLSLWIDGET_H
