#ifndef PNG_HEADER
#define PNG_HEADER

#include <png.h>
#include <string>
#include <cstdio>
#include <cstdlib>

class Image_PNG
{
  private:
  public:
    int width, height, bit_depth, color_type;
    png_structp data;
    void load(std::string filename);
};

#endif
