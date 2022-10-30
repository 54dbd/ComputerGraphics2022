#include "glslwidget.h"
#include <QApplication>

int runGLSL(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLSLWidget w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}
