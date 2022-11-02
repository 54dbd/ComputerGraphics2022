#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include "vbotorus.h"
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>

class QOpenGLShaderProgram;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget( int& N, double& KDKS, QWidget *parent = 0);
    ~OpenGLWidget();
public slots:
    void nextFrame();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QOpenGLShaderProgram *program;
    VBOTorus *torus;
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    GLfloat xtrans, ytrans, ztrans; // translation on x,y,z-axis
    QVector2D mousePos;
    QQuaternion rotation;

    QOpenGLTexture *texture;

    int &n;
    double &kdks;
};

#endif // OPENGLWIDGET_H
