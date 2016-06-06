#include "map.hpp"

Map::Map(float tile_width)
{
  window = new Window;
  state = new State;
  w = tile_width;
}

Map::~Map()
{
  delete window;
  delete state;
  for(int i = 0; i < tiles.size(); i++) {
    delete tiles[i];
  }
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
  tiles.push_back(new Tile(x_coord, y_coord, w, texture_filename));
  state->add(tiles[tiles.size() - 1]->model);
}
