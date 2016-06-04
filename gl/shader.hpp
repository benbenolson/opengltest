#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"
#include <string>
#include <cstdio>
#include <cstdlib>

class Shader
{
  public:
    Shader();
    Shader(const GLchar *vertexSource, const GLchar *fragmentSource);
  private:
    void createShader(const GLchar *vertexSource, const GLchar *fragmentSource);
    GLuint program;
    void checkErrors();
};

#endif
