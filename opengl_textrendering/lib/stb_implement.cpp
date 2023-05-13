#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_implement.h"

stb_implement::stb_implement(const char* location)
{
	// Constructor loads the image to image pointer
	int numChannels;
	image = stbi_load(location, &image_width, &image_height, &numChannels, 0);
}

stb_implement::~stb_implement()
{
	// Clean up the loaded image data
	stbi_image_free(image);
}
