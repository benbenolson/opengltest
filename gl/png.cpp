#include "png.hpp"

Image_PNG::Image_PNG(std::string filename)
{
  int header_size = 8;
  png_structp png_ptr;
  png_bytep header = (png_bytep)malloc(8);
  FILE *fp = fopen(filename.c_str(), "r");
  data = NULL;
  
  // Test for file existence and read in the header
  if(fp) {
    fread(header, 1, header_size, fp);
  } else {
    std::cerr << "Error reading the file: '" << filename << "'." << std::endl;
    exit(1);
  }
  
  // Make sure it's a PNG
  if(png_sig_cmp(header, 0, header_size)) {
    std::cerr << "'" << filename << "' is not a valid PNG file." << std::endl;
    exit(1);
  }

  // Initialize some libPNG stuff
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(png_ptr == NULL) {
    std::cerr << "Failed to create read struct while reading '" << filename << "'." << std::endl;
  }
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(info_ptr == NULL) {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    std::cerr << "Failed to create info struct while reading '" << filename << "'." << std::endl;
    exit(1);
  }
  png_infop end_ptr = png_create_info_struct(png_ptr);
  if(end_ptr == NULL) {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    std::cerr << "Failed to create end info struct while reading '" << filename << "'." << std::endl;
    exit(1);
  }
  
  // Tell libpng that this is the file that we're reading from
  png_init_io(png_ptr, fp);

  // Tell libpng that we already read the first `header_size` bytes.
  png_set_sig_bytes(png_ptr, header_size);

  //Read in information about the image
//  png_read_info(png_ptr, info_ptr);

  // Read in the entire image
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  data = png_get_rows(png_ptr, info_ptr);
}
