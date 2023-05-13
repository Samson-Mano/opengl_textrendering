#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../lib/stb_image.h"
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(const std::string& filepath);
	void Bind(unsigned int slot = 0) const;
	void UnBind();

	inline int GetWidth() const { return texture_width; }
	inline int GetHeight() const { return texture_height; }
private:
	unsigned int texture_id;
	std::string texture_filepath;
	unsigned char* local_buffer;
	int texture_width, texture_height, texture_bpp;
};

