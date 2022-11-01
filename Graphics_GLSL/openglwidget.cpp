#include "openglwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QWheelEvent>

OpenGLWidget::OpenGLWidget( int &N, double &KDKS, QWidget *parent)
    :QOpenGLWidget(parent)
    ,xtrans(0),ytrans(0),ztrans(0.0)
    ,n(N),kdks(KDKS)
{

}

OpenGLWidget::~OpenGLWidget()
{
    delete torus;
    delete program;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // vertex shader
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceFile(":/shader/function.vert");
    // fragment shader
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceFile(":/shader/function.frag");

    // shader program
    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);

    program->link();
    program->bind();

    // set color used to clear background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // vertices array
    torus = new VBOTorus(1.0f,60, 60);

    // texture
    QImage image = QImage(":/shader/R.jpg").mirrored(false,true);
    texture = new QOpenGLTexture(image, QOpenGLTexture::GenerateMipMaps);
    // set the texture wrapping parameters
    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);


    // view matrix
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));

    // uniform light/material property
    QVector4D worldLight = QVector4D(5.0f,5.0f,2.0f,1.0f);
    program->setUniformValue("Material.Kd", 0.3f, 0.7f, 0.9f);
//    program->setUniformValue("Material.Kd", 0.9f, 0.5f, 0.3f);
    program->setUniformValue("Light.Ld", 1.0f, 1.0f, 1.0f);
    program->setUniformValue("Light.Position", view * worldLight );
//    program->setUniformValue("Material.Ka", 0.9f, 0.5f, 0.3f);
    program->setUniformValue("Material.Ka", 0.3f, 0.7f, 0.9f);
    program->setUniformValue("Light.La", 0.4f, 0.4f, 0.4f);
    program->setUniformValue("Material.Ks", 0.8f, 0.8f, 0.8f);
    program->setUniformValue("Light.Ls", 1.0f, 1.0f, 1.0f);
    program->setUniformValue("Material.Shininess", 100.0f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w/2,h/2);
    projection.setToIdentity();
    projection.perspective(60.0f, (GLfloat)w/(GLfloat)h, 0.001f, 100.0f);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // transform the model
    model.setToIdentity();
    model.translate(xtrans, ytrans, ztrans);
    model.rotate(rotation);
    QMatrix4x4 mv = view * model;
    program->setUniformValue("ModelViewMatrix", mv);
    program->setUniformValue("NormalMatrix",
                             mv.normalMatrix());
    program->setUniformValue("MVP", projection * mv);
//    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    program->bind();
    // render the object
    torus->render();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    event->accept();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePos;
        qreal angle = (diff.length())/3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePos = newPos;
        this->update();
    }
    event->accept();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() > 0) {
        ztrans += 0.25f;
    } else if (numDegrees.y() < 0) {
        ztrans -= 0.25f;
    }
    this->update();
    event->accept();
}
