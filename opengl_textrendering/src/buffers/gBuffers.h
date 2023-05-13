#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class gBuffers
{
public:
	gBuffers();
	~gBuffers();
	void Bind()const;
	void UnBind()const;
	void CreateBuffers(const void* vb_data, 
		unsigned int& vb_size, 
		const unsigned int* ib_indices, 
		unsigned int& ib_count, 
		VertexBufferLayout& layout);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer ibo;
private:

};
