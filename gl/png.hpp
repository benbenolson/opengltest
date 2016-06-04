#ifndef PNG_HEADER
#define PNG_HEADER

#include <png.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

class Image_PNG
{
  public:
    int width, height, bit_depth, color_type;
    png_bytep *data;
    Image_PNG(std::string filename);
};

#endif
