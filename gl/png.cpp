#include "png.hpp"

void Image_PNG::load(std::string filename)
{
  int header_size = 8;
  png_bytep header = (png_bytep)malloc(8);
  FILE *fp = fopen(filename.c_str(), "r");
  
  // Test for file existence and read in the header
  if(!fp) {
    fread(header, 1, header_size, fp);
  } else {
    fprintf(stderr, "Error reading the file: %s\n", filename.c_str());
    exit(1);
  }
  
  // Make sure it's a PNG
  if(png_sig_cmp(header, 0, header_size)) {
    fprintf(stderr, "%s is not a valid PNG file.\n", filename.c_str());
    exit(1);
  }

  // Initialize some libPNG stuff
  data = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(data == NULL) {
    fprintf(stderr, "Failed to create read struct while reading %s.\n", filename.c_str());
  }
  png_infop info_ptr = png_create_info_struct(data);
  if(info_ptr == NULL) {
    png_destroy_read_struct(&data, (png_infopp)NULL, (png_infopp)NULL);
    fprintf(stderr, "Failed to create info struct while reading %s.\n", filename.c_str());
    exit(1);
  }
  png_infop end_ptr = png_create_info_struct(data);
  if(end_ptr == NULL) {
    png_destroy_read_struct(&data, (png_infopp)NULL, (png_infopp)NULL);
    fprintf(stderr, "Failed to create end info struct while reading %s.\n", filename.c_str());
    exit(1);
  }
  
  // Tell libpng that this is the file that we're reading from
  png_init_io(data, fp);

  // Tell libpng that we already read the first `header_size` bytes.
  png_set_sig_bytes(data, header_size);

  //Read in information about the image
  png_read_info(data, info_ptr);

  // Read in the entire image
  png_read_png(data, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);
}
