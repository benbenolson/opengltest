#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

class Shader
{
  public:
    Shader();
    GLuint program;
  private:
    void createShader(const GLchar *vertexSource, const GLchar *fragmentSource);
    void checkErrors();
};

#endif
