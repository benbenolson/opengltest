#include "shader.hpp"
#include "window.hpp"
#include "opengl.hpp"
#include "model.hpp"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void draw(State *state)
{
  state->model->draw();
}

int main(int argc, char **argv)
{
  Window window;
  Shader shader;

  // Triangle of vertices
  GLfloat vertices[] = {
    0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1 (X, Y)
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2 (X, Y)
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Vertex 3 (X, Y)
  };

  Model base(vertices);
  State state;
  state.model = &base;

  window.eventLoop(draw, &state);
}
