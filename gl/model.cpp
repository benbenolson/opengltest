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

Model::Model(GLfloat *vertices, size_t vboSize, GLuint *elements, size_t eboSize, std::string texture_filename)
{
  size = vboSize;

  // Create and activate the VBO
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Copy the vertices to the graphics card
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

  // Read in the texture
  Image_PNG png = Image_PNG(texture_filename);

  // Load the image data into a texture
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, png.width, png.height, 0, \
               GL_RGBA, GL_UNSIGNED_BYTE, png.data);

  // Set parameters
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,
                       (void *)(6 * sizeof(GLfloat)));

  std::cout << "Generating texture " << texture_id << std::endl;
//  glBindVertexArray(0);
}

// Draw the model to the screen
void Model::draw(GLuint program)
{
  // Bind the texture
  glActiveTexture(GL_TEXTURE0);
  std::cout << "Binding texture" << std::endl;
  glBindTexture(GL_TEXTURE_2D, texture_id);
  checkErrors();
  std::cout << "Uniform" << std::endl;
  glUniform1i(texture_id, 0);
  checkErrors();

  std::cout << "Binding buffer" << std::endl;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  checkErrors();

  glBindVertexArray(vao);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
