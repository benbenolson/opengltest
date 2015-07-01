#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "shader.hpp"
#include "opengl.hpp"
#include <string>
#include <cstdio>

class Model
{
  private:
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    void checkErrors();
    GLuint size;
  public:
    Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize);
    void print();
    void draw();
};

#endif
