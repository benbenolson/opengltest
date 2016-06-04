#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "shader.hpp"
#include "opengl.hpp"
#include "png.hpp"
#include <string>
#include <cstdio>

class Model
{
  private:
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint texture_id;
    void checkErrors();
    GLuint size;
  public:
    Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize, std::string texture_filename);
    void print();
    void draw(GLuint program);
};

#endif
