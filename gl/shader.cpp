#include "shader.hpp"

using namespace std;

void Shader::checkErrors()
{
  std::string message;
  GLenum error = glGetError();
  switch(error) {
    case GL_INVALID_ENUM: message = "Invalid enum."; break;
    case GL_INVALID_VALUE: message = "Invalid value."; break;
    case GL_INVALID_OPERATION: message = "Invalid operation."; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: message = "Invalid framebuffer operation."; break;
    case GL_OUT_OF_MEMORY: message = "Out of memory."; break;
    case GL_STACK_UNDERFLOW: message = "Stack underflow."; break;
    case GL_STACK_OVERFLOW: message = "Stack overflow."; break;
  }
  if(error) {
    fprintf(stderr, "SHADER ERROR: %s\n", message.c_str());
  }
}

Shader::Shader()
{
  // Default shaders
  const GLchar *vertexSource =
      "#version 150 core\n"
      "in vec3 position;\n"
      "in vec3 color;\n"
      "out vec3 Color;\n"
      "void main()\n"
      "{\n"
      "   Color = color;\n"
      "   gl_Position = vec4(position, 1.0);\n"
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
  checkErrors();
  // Load the vertex shader onto the graphics card and compile it
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Error checking for the vertex shader
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

  // Error checking for the fragment shader
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

  // Set the attribute locations
  glBindAttribLocation(shaderProgram, 0, "position");
  glBindAttribLocation(shaderProgram, 1, "color");

  // Bind and Link the program
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
  
  // Error checking for the GPU program
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if(status == GL_TRUE) {
    printf("Shader program linked successfully.\n");
  } else {
    fprintf(stderr, "The shader program did not link correctly.\n");
  }

  // Clean up 
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Return the shader program
  return shaderProgram;
}
