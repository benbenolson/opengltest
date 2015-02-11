#include "shader.hpp"
#include <cstdio>
#include <cstdlib>

using namespace std;

Shader::Shader()
{
  // Default shaders
  const GLchar *vertexSource =
      "#version 150 core\n"
      "in vec2 position;\n"
      "in vec3 color;\n"
      "out vec3 Color;\n"
      "void main()\n"
      "{\n"
      "   Color = color;\n"
      "   gl_Position = vec4(position, 0.0, 1.0);\n"
      "}\n";
  const GLchar *fragmentSource =
      "#version 150 core\n"
      "in vec3 Color;\n"
      "out vec4 outColor;\n"
      "void main() {\n"
      "   outColor = vec4(Color, 1.0);\n"
      "}\n";
  program = createShader(vertexSource, fragmentSource);
}

Shader::Shader(const GLchar *vertexSource, const GLchar *fragmentSource)
{
  program = createShader(vertexSource, fragmentSource);
}

GLuint Shader::get()
{
  return program;
}

GLuint Shader::createShader(const GLchar *vertexSource, const GLchar *fragmentSource)
{
  // Load the vertex shader onto the graphics card and compile it
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if(status == GL_TRUE) {
    printf("Loaded vertex shader successfully.\n");
  } else {
    fprintf(stderr, "The vertex shader did not compile successfully.\n");
  }

  // Do the same to the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if(status == GL_TRUE) {
    printf("Loaded fragment shader successfully.\n");
  } else {
    fprintf(stderr, "The fragment shader did not compile successfully.\n");
  }

  // Now create a program from the two shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if(status == GL_TRUE) {
    printf("Shader program linked successfully.\n");
  } else {
    fprintf(stderr, "The shader program did not link correctly.\n");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Set the attribute locations
  glBindAttribLocation(shaderProgram, 0, "position");
  glBindAttribLocation(shaderProgram, 1, "color");

  // Return the shader program
  return shaderProgram;
}
