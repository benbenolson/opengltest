#include "gl/shader.hpp"
#include "gl/window.hpp"
#include "gl/opengl.hpp"
#include "gl/model.hpp"
#include "gl/state.hpp"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void draw(State *state)
{
  state->models[0]->draw();
  state->models[1]->draw();
}

int main(int argc, char **argv)
{
  // First three are x,y,z; last three are r,g,b
  float vertices[] = {
    -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Top-left 0
    -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Top-right 1
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-right 2
    -1.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f // Bottom-left 3
  };
  float vertices2[] = {
    -0.75f, 0.75f, 0.0f, 0.0f, 1.0f, 0.0f, // Top-left 0
    -0.25f, 0.75f, 0.0f, 0.0f, 1.0f, 0.0f, // Top-right 1
    -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // Bottom-right 2
    -0.75f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f // Bottom-left 3
  };

  // The order of the vertices above that will be drawn with gldrawelements()
  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  Window window;
  Shader shader;
  Model base(vertices, sizeof(vertices), elements, sizeof(elements));
  Model base2(vertices2, sizeof(vertices2), elements, sizeof(elements));
  State state;
  state.models.push_back(&base);
  state.models.push_back(&base2);

  window.eventLoop(draw, &state);
}
