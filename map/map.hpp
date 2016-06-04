#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include "tile.hpp"
#include "../gl/window.hpp"
#include "../gl/shader.hpp"
#include "../gl/state.hpp"

class Map {
  private:
    std::vector<Tile> tiles;
    Window *window;
    State *state;
    GLuint *elements;
    float w;
  public:
    Map(float tile_width);
    void draw();
    void add_tile(float x_coord, float y_coord, std::string texture_filename);
    bool should_close();
};

#endif
