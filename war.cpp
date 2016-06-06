#include "map/map.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
  Map map = Map(0.3f);
  map.add_tile(-1.0f, 1.0f, "textures/youtube-32x32.png");
  while(!map.should_close()) {
    map.draw();
  }
}
