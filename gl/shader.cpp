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
      "#version 330 core\n"
      "layout(location = 0) in vec3 position;\n"
      "layout(location = 1) in vec3 color;\n"
      "layout(location = 2) in vec2 texture_coord;\n"
      "out vec3 Color;\n"
      "out vec2 Texture_coord;\n"
      "void main()\n"
      "{\n"
      "   Color = color;\n"
      "   Texture_coord = texture_coord;\n"
      "   gl_Position = vec4(position, 1.0);\n"
      "}\n";
  const GLchar *fragmentSource =
      "#version 330 core\n"
      "in vec3 Color;\n"
      "in vec2 Texture_coord;\n"
      "out vec4 outColor;\n"
      "uniform sampler2D texture;\n"
      "void main() {\n"
      "   outColor = texture2D(texture, Texture_coord);\n"
      "}\n";
  createShader(vertexSource, fragmentSource);
}

Shader::Shader(const GLchar *vertexSource, const GLchar *fragmentSource)
{
  createShader(vertexSource, fragmentSource);
}

void Shader::createShader(const GLchar *vertexSource, const GLchar *fragmentSource)
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
  program = glCreateProgram();
  std::cout << "Created shader program " << program << std::endl;
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Set the attribute locations
  //glBindAttribLocation(program, 0, "position");
  //glBindAttribLocation(program, 1, "color");
  //glBindAttribLocation(program, 2, "texture");

  // Bind and Link the program
  glBindFragDataLocation(program, 0, "outColor");
  glLinkProgram(program);
  glUseProgram(program);
  
  // Error checking for the GPU program
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(status == GL_TRUE) {
    printf("Shader program linked successfully.\n");
  } else {
    fprintf(stderr, "The shader program did not link correctly.\n");
  }

  // Clean up 
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
