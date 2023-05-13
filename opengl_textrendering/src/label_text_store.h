#pragma once
#include <iostream>
#include <glm/vec2.hpp>
#include "buffers/gBuffers.h"
#include "font_atlas.h"

struct label_text
{
	// Store the individual label
	const char* label;
	glm::vec2 label_loc;
	glm::vec3 label_color;
	float label_angle;
	float label_size;
};

class label_text_store
{
	// Stores all the labels
public:
	font_atlas main_font;
	unsigned int total_char_count = 0;
	gBuffers label_buffers;
	std::vector<label_text> labels;

	label_text_store();
	~label_text_store();
	void init();
	void add_text(const char* text, glm::vec2 text_loc, glm::vec3 text_color,
		float geom_scale, float font_angle, float font_size);
	void set_buffers();
	void paint_text();
private:
	void get_buffer(label_text& label, float* vertices, unsigned int& vertex_index, unsigned int* indices, unsigned int& indices_index);
	glm::vec2 rotate_pt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle);

};
