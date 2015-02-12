#include "shader.hpp"
#include "window.hpp"
#include "opengl.hpp"
#include "model.hpp"
#include "state.hpp"
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
  float vertices[] = {
    -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // Top-left
     1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // Top-right
     1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f  // Bottom-left
  };

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };


  Window window;
  Shader shader;
  Model base(vertices, sizeof(vertices), elements, sizeof(elements));
  State state;
  state.model = &base;

  window.eventLoop(draw, &state);
}
