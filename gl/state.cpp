#include "state.hpp"

State::State()
{
  size = 0;
}

void State::add(Model *model)
{
  models.push_back(*model);
  size++;
}

void State::drawall()
{
  for(int i = 0; i < size; ++i) {
    models[i].draw();
  }
}