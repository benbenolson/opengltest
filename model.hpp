#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "shader.hpp"
#include "opengl.hpp"

class Model
{
  private:
    GLuint vao;
  public:
    Model(GLfloat *vertices);
    void draw();
};

#endif
