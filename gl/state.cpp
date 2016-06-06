#include "state.hpp"

State::State()
{
  shader = new Shader;
  size = 0;
}

State::~State()
{
  delete shader;
}

void State::add(Model *model)
{
  models.push_back(*model);
  size++;
}

void State::drawall()
{
  glUseProgram(shader->program);
  for(int i = 0; i < size; ++i) {
    models[i].draw(shader->program);
  }
}
