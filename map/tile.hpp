#ifndef TILE_HEADER
#define TILE_HEADER

#include "../gl/model.hpp"
#include <iostream>
#include <string>

class Tile
{
  public:
    Tile(float x_coord, float y_coord, float tile_width, std::string texture_filename);
    ~Tile();
    float x, y, width;
    Model *model;
};

#endif
