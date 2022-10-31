#ifndef VBOTORUS_H
#define VBOTORUS_H
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class QOpenGLVertexArrayObject;
class VBOTorus : protected QOpenGLFunctions
{
public:
    VBOTorus(float outerRadius, int nrings, int nsides);
    ~VBOTorus();
    void render();
    int getVertexArrayHandle();
protected:
    QOpenGLVertexArrayObject vao;
private:
    int faces, rings, sides;
    void generateVerts(float * verts, float * norms, float * tex,
                       unsigned int * el,
                       float outerRadius );
};

#endif // VBOTORUS_H
