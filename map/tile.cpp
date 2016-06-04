#include "tile.hpp"

Tile::Tile(float x_coord, float y_coord, float tile_width, std::string texture_filename)
{
  float v[24];
  int i;

  x = x_coord;
  y = y_coord;
  width = tile_width;

  v[0] = x_coord;
  v[1] = y_coord - tile_width;
  for(i = 2; i <= 5; i++) {
    v[i] = 0.0f;
  }
  v[3] = 1.0f;

  v[6] = x_coord + tile_width;
  v[7] = y_coord - tile_width;
  for(i = 8; i <= 11; i++) {
    v[i] = 0.0f;
  }
  v[9] = 1.0f;

  v[12] = x_coord;
  v[13] = y_coord;
  for(i = 14; i <= 17; i++) {
    v[i] = 0.0f;
  }
  v[15] = 1.0f;

  v[18] = x_coord + tile_width;
  v[19] = y_coord;
  for(i = 20; i <= 23; i++) {
    v[i] = 0.0f;
  }
  v[21] = 1.0f;
  
  int n = 0;
  for(i = 0; i < 24; i++) {
    std::cout << v[i] << " ";
    n++;
    if(n == 6) {
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
