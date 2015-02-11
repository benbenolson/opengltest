#include "model.hpp"
#include <cstdio>

Model::Model(GLfloat *vertices)
{
  // Create the VBO
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create the VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Set the position attributes
  GLint posAttrib = 0;
  GLint colAttrib = 1;
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

  // Set the color attributes
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

  glDeleteBuffers(1, &vbo);
}

void Model::draw()
{
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
