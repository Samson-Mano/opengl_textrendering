#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void createVertexBuffer(const void* data, unsigned int size);
	void Bind() const;
	void UnBind() const;
private:
	unsigned int vb_id;
};
