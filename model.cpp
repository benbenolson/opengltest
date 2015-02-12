#include "model.hpp"
#include <cstdio>

Model::Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize)
{
  // Create and activate the VBO
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Copy the vertices to the graphics card
  printf("Copying an array of size %lu.\n", vboSize);
  glBufferData(GL_ARRAY_BUFFER, vboSize, vertices, GL_STATIC_DRAW);

  // Create the VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create the EBO
  GLuint ebo;
  glGenBuffers(1, &ebo);

  // Bind the EBO and copy it to the GPU
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, elements, GL_STATIC_DRAW);

  // Set the position attributes
  GLint posAttrib = 0;
  GLint colAttrib = 1;
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

  // Set the color attributes
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

  glBindVertexArray(0);
  glDeleteBuffers(1, &vbo);
}

void Model::draw()
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
