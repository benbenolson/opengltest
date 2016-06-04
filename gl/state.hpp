#ifndef STATE_HEADER
#define STATE_HEADER

#include "model.hpp"
#include "shader.hpp"
#include <vector>

struct State
{
  private:
    std::vector<Model> models;
    Shader *shader;
  public:
    State();
    void add(Model *model);
    void drawall();
    int size;

};

#endif
