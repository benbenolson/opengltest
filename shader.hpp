#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"

class Shader
{
  public:
    Shader();
    Shader(const GLchar *vertexSource, const GLchar *fragmentSource);
    GLuint get();
  private:
    GLuint createShader(const GLchar *vertexSource, const GLchar *fragmentSource);
    GLuint program;
};

#endif
