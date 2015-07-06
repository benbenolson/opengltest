#include "floor.hpp"
#include "gl/png.hpp"
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
  state->drawall();
}

int main(int argc, char **argv)
{
  // The order of the vertices above that will be drawn with gldrawelements()
  GLuint elements[] = {
    0, 1, 2,
    2, 1, 3
  };

  Window window;
  Shader shader;
  State state;
  for(int i = 0; i < FLOORSIZE; ++i) {
    Model floor(v[i], sizeof(v[i]), elements, sizeof(elements));
    state.add(&floor);
  }

  window.eventLoop(draw, &state);
}
