#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "shader.hpp"
#include "opengl.hpp"

class Model
{
  private:
    GLuint vao;
  public:
    Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize);
    void draw();
};

#endif
