#include "map.hpp"

Map::Map(float tile_width)
{
  window = new Window;
  shader = new Shader;
  state = new State;
  w = tile_width;
}

bool Map::should_close()
{
  return window->should_close();
}

void Map::draw()
{
  window->handle_keys();
  window->clear_window();
  state->drawall();
  window->post_draw();
}

void Map::add_tile(float x_coord, float y_coord, std::string texture_filename) {
  tiles.push_back(Tile(x_coord, y_coord, w, texture_filename));
  state->add(tiles[tiles.size() - 1].model);
}
