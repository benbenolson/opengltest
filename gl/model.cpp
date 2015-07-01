#include "model.hpp"

void Model::checkErrors()
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
    fprintf(stderr, "MODEL ERROR: %s\n", message.c_str());
  }
}

Model::Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize)
{
  size = vboSize;

  // Create and activate the VBO
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Copy the vertices to the graphics card
  printf("Copying an array of size %lu.\n", vboSize);
  glBufferData(GL_ARRAY_BUFFER, vboSize, vertices, GL_STATIC_DRAW);

  // Create the VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create the EBO
  glGenBuffers(1, &ebo);

  // Bind the EBO and copy it to the GPU
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, elements, GL_STATIC_DRAW);

  // Set the position attributes
  GLint posAttrib = 0;
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

  // Set the color attributes
  GLint colAttrib = 1;
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
}

// Draw the model to the screen
void Model::draw()
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  checkErrors();
  glBindVertexArray(0);
}

// Print out the vertex array
void Model::print()
{
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  float *data = (float *)glMapBufferRange(GL_ARRAY_BUFFER, 0, size, 
                                          GL_MAP_READ_BIT);
  for(int i = 0; i < size / sizeof(float); ++i) {
    printf("%f\n", *(data++));
  }
  glUnmapBuffer(GL_ARRAY_BUFFER);
  checkErrors();
}
