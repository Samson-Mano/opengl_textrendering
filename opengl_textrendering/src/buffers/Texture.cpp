#include "Texture.h"

Texture::Texture()
	: texture_id(0), texture_filepath(""), local_buffer(nullptr), texture_width(0), texture_height(0), texture_bpp(0)
{
	// Initialize texture data members
}

Texture::~Texture()
{
	// Free the local buffer if it has been allocated
	if (local_buffer)
		stbi_image_free(local_buffer);

	// Delete the OpenGL texture if it has been created
	if (texture_id)
		glDeleteTextures(1, &texture_id);
}

void Texture::Bind(unsigned int slot) const
{
	// Activate a texture slot
	glActiveTexture(GL_TEXTURE0 + slot);

	// Bind the texture to the slot
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::UnBind()
{
	// Unbind the current texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadTexture(const std::string& filepath)
{
	int width, height, bpp;

	// Flip the texture file ??
	// stbi_set_flip_vertically_on_load(1);

	// Load the texture from file using stb_image library
	local_buffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

	if (!local_buffer)
	{
		// Handle failure to load texture
		std::cout << "Failed to load texture: " << filepath << std::endl;
	}

	// Generate a new texture in OpenGL and bind it
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Upload the texture data to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set the texture properties
	texture_filepath = filepath;
	texture_width = width;
	texture_height = height;
	texture_bpp = bpp;

	// Free the image data
	// stbi_image_free(local_buffer);
}