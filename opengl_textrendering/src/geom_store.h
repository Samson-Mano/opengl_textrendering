#pragma once
#include "buffers/gBuffers.h"
#include "shaders/shader.h"
#include "label_text_store.h"

class geom_store
{
public:

	geom_store();
	~geom_store();
	void set_geometry();
	void paint_geometry();
private:
	void set_simple_triangle(float* vertices, unsigned int& vertices_count,
		unsigned int* indices, unsigned int& indices_count);
	gBuffers tri_buffers;
	label_text_store all_labels;

	shader tri_shader;
	shader text_shader;
};
