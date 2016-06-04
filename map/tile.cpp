#include "tile.hpp"

Tile::Tile(float x_coord, float y_coord, float tile_width, std::string texture_filename)
{
  float v[32];
  int i;

  x = x_coord;
  y = y_coord;
  width = tile_width;

  v[0] = x_coord;
  v[1] = y_coord - tile_width;
  for(i = 2; i <= 7; i++) {
    v[i] = 0.0f;
  }
  v[5] = 1.0f;

  v[8] = x_coord + tile_width;
  v[9] = y_coord - tile_width;
  for(i = 10; i <= 13; i++) {
    v[i] = 0.0f;
  }
  v[11] = 1.0f;

  v[14] = x_coord;
  v[15] = y_coord;
  for(i = 16; i <= 19; i++) {
    v[i] = 0.0f;
  }
  v[17] = 1.0f;

  v[20] = x_coord + tile_width;
  v[21] = y_coord;
  for(i = 22; i <= 25; i++) {
    v[i] = 0.0f;
  }
  v[23] = 1.0f;
  
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

  model = new Model(v, sizeof(v), elements, sizeof(elements), texture_filename);
}
