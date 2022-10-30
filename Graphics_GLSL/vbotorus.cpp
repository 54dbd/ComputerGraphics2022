#include "vbotorus.h"
#include <QOpenGLVertexArrayObject>
#include <QtMath>
#include <math.h>
//nrings:外圈面数
//nsides:切面圆面数
VBOTorus::VBOTorus(float outerRadius , int nrings, int nsides)
    :rings(nrings), sides(nsides)
{
    initializeOpenGLFunctions();
    faces = sides * rings;
    int nVerts  = sides * (rings+1);   // One extra ring to duplicate first ring

    // Verts
    float * v = new float[3 * nVerts];
    // Normals
    float * n = new float[3 * nVerts];
    // Tex coords
    float * tex = new float[2 * nVerts];
    // Elements
    unsigned int * el = new unsigned int[6 * faces];

    // Generate the vertex data
    generateVerts(v, n, tex, el, outerRadius);

    // Create and populate the buffer objects
    unsigned int handle[4];
    glGenBuffers(4, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * faces * sizeof(unsigned int), el, GL_STATIC_DRAW);

    delete [] v;
    delete [] n;
    delete [] el;
    delete [] tex;

    // Create the VAO
    vao.create();
    vao.bind();
//    glGenVertexArrays(1, vaoHandle);
//    glBindVertexArray(vaoHandle);

//    glGenVertexArrays( 1, &vaoHandle );
//    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

    glEnableVertexAttribArray(1);  // Vertex normal
    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glEnableVertexAttribArray(2);  // Texture coords
    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);

    vao.release();
//    glBindVertexArray(0);
}

VBOTorus::~VBOTorus()
{
//    delete vao;
}

void VBOTorus::render()
{
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
    vao.release();
}

//int VBOTorus::getVertexArrayHandle()
//{
//    return faces;
//}

//QOpenGLVertexArrayObject VBOTorus::getVertexArrayHandle()
//{
//    return vao;
//}

void VBOTorus::generateVerts(float *verts, float *norms, float *tex, unsigned int *el, float outerRadius)
{
    float ringFactor = 2.0f * M_PI / rings;
    float sideFactor = 1.0385f * M_PI / sides;//PI精度原因，1.0会导致闭合不完全
    int idx = 0, tidx = 0;
    for( int ring = 0; ring <= rings; ring++ ) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for( int side = 0; side < sides; side++ ) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = outerRadius;

            /*ORIGINAL*/
//            verts[idx] = r * cu;                //x
//            verts[idx + 1] = r * su;            //y
//            verts[idx + 2] = innerRadius * sv;  //z

//            norms[idx] = cv * cu * r;           //x_n
//            norms[idx + 1] = cv * su * r;       //y_n
//            norms[idx + 2] = sv * r;            //z_n
            /*VER1.0*/
            verts[idx] = r * sv * su;                //x
            verts[idx + 1] = r * cv;            //y
            verts[idx + 2] = r * sv * cu;  //z

            norms[idx] = r * sv * su;           //x_n
            norms[idx + 1] = r * cv;       //y_n
            norms[idx + 2] = r * sv * cu;            //z_n

            tex[tidx] = u / (2.0 * M_PI);
            tex[tidx + 1] = v / (1.0385 * M_PI);
            tidx += 2;

            // Normalize
            float len = qSqrt( norms[idx] * norms[idx] +
                               norms[idx+1] * norms[idx+1] +
                    norms[idx+2] * norms[idx+2] );
            norms[idx] /= len;          //x_n
            norms[idx+1] /= len;        //y_n
            norms[idx+2] /= len;        //z_n
            idx += 3;
        }
    }

    idx = 0;
    for( int ring = 0; ring < rings; ring++ ) {
        int ringStart = ring * sides;
        int nextRingStart = (ring + 1) * sides;
        for( int side = 0; side < sides; side++ ) {
            int nextSide = (side+1) % sides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx+1] = (nextRingStart + side);
            el[idx+2] = (nextRingStart + nextSide);
            el[idx+3] = ringStart + side;
            el[idx+4] = nextRingStart + nextSide;
            el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }
}
