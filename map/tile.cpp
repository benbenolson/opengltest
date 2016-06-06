#include "tile.hpp"

Tile::Tile(float x_coord, float y_coord, float tile_width, std::string texture_filename)
{
  float v[32];
  int i;

  x = x_coord;
  y = y_coord;
  width = tile_width;

  // Bottom left
  v[0] = x_coord;
  v[1] = y_coord - tile_width;
  for(i = 2; i <= 7; i++) {
    v[i] = 0.0f;
  }
  v[7] = 1.0f;
  v[5] = 1.0f;

  // Bottom right
  v[8] = x_coord + tile_width;
  v[9] = y_coord - tile_width;
  for(i = 10; i <= 15; i++) {
    v[i] = 0.0f;
  }
  v[14] = 1.0f;
  v[15] = 1.0f;
  v[11] = 1.0f;

  // Top left
  v[16] = x_coord;
  v[17] = y_coord;
  for(i = 18; i <= 23; i++) {
    v[i] = 0.0f;
  }
  v[19] = 1.0f;

  // Top right
  v[24] = x_coord + tile_width;
  v[25] = y_coord;
  for(i = 26; i <= 31; i++) {
    v[i] = 0.0f;
  }
  v[30] = 1.0f;
  v[27] = 1.0f;
  
  int n = 0;
  for(i = 0; i < 32; i++) {
    std::cout << v[i] << " ";
    n++;
    if(n == 8) {
      std::cout << std::endl;
      n = 0;
    }
  }

  GLuint elements[] = {
    0, 1, 2,
    2, 1, 3
  };

  // Create a new model to represent this tile, and store it
  model = new Model(v, sizeof(v),
                    elements, sizeof(elements),
                    texture_filename);
}

Tile::~Tile()
{
  delete model;
}
