#ifndef STATE_HEADER
#define STATE_HEADER

#include "model.hpp"
#include <vector>

struct State
{
  std::vector<Model *> models;
};

#endif
