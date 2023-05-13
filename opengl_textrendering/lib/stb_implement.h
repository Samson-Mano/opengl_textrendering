#pragma once
// can't put #define STB_IMAGE_IMPLEMENTATION in a header file. 
// Only one source file can see the #define.
// So the STB implementation is done in stb_implement.cpp to avoid linker error

class  stb_implement
{
public:
	unsigned char* image;
	int image_width;
	int image_height;

	// Constructor and Destructor
	stb_implement(const char* location);

	~stb_implement();

	// Functions
private:

};
