#include <GLCommon.h>

class SamplePolygon
{
public:
    SamplePolygon();

    void init_triangle(GLuint *, GLuint *, GLuint *);
    void init_cube(GLuint *, GLuint *, GLuint *);

private:
    void init_buf(GLuint *, GLuint *, GLuint *, GLuint, GLuint, GLfloat **, GLfloat **);
};