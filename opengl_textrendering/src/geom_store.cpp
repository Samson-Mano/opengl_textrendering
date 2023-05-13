#include "geom_store.h"

geom_store::geom_store()
{
}

geom_store::~geom_store()
{
}

void geom_store::set_geometry()
{
	// Set the geometry
	unsigned int node_vertices_count = 6 * 3;
	float* node_vertices = new float[node_vertices_count];

	unsigned int node_indices_count = 3;
	unsigned int* node_indices = new unsigned int[node_indices_count];

	unsigned int node_vertex_index = 0;
	unsigned int node_indices_index = 0;

	set_simple_triangle(node_vertices, node_vertex_index, node_indices, node_indices_index);

	VertexBufferLayout vb_tri;
	vb_tri.AddFloat(3);
	vb_tri.AddFloat(3);

	// Create the buffers
	unsigned int node_vertices_size = node_vertices_count * sizeof(float);
	tri_buffers.CreateBuffers(node_vertices, node_vertices_size, node_indices, node_indices_count, vb_tri);

	// Create the shader
	tri_shader.create_shader("src/shaders/basic_vert_shader.vert", "src/shaders/basic_frag_shader.frag");

	// Shader for the text
	text_shader.create_shader("src/shaders/text_vert_shader.vert", "src/shaders/text_frag_shader.frag");
	text_shader.setUniform("zoomscale", 1.0f);
	text_shader.setUniform("u_Texture", 0);

	// Add the labels
	all_labels.init();
	 all_labels.add_text("Length = 98.76532101", glm::vec2(-0.8, -0.3), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f, 45, 0.0004f);
	 all_labels.add_text("Pulled Pork Sandwich!!", glm::vec2(-0.4, 0), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, -15, 0.0003f);
	 all_labels.add_text("Hello@", glm::vec2(-0.8, 0.3), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 5.0f, 0.0003f);

	// all_labels.add_text("C", glm::vec2(-0.8, -0.6), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0, 0.04f, 0, 0);
	all_labels.set_buffers();

}


void geom_store::set_simple_triangle(float* vertices, unsigned int& vertices_index,
	unsigned int* indices, unsigned int& indices_index)
{

	// Point 1
	vertices[vertices_index + 0] = -0.5;
	vertices[vertices_index + 1] = -0.5;
	vertices[vertices_index + 2] = 0.0f;

	vertices[vertices_index + 3] = 1.0f;
	vertices[vertices_index + 4] = 1.0f;
	vertices[vertices_index + 5] = 1.0f;

	vertices_index = vertices_index + 6;

	// Point 2
	vertices[vertices_index + 0] = 0.5;
	vertices[vertices_index + 1] = -0.5;
	vertices[vertices_index + 2] = 0.0f;

	vertices[vertices_index + 3] = 1.0f;
	vertices[vertices_index + 4] = 1.0f;
	vertices[vertices_index + 5] = 1.0f;

	vertices_index = vertices_index + 6;

	// Point 3
	vertices[vertices_index + 0] = 0.0;
	vertices[vertices_index + 1] = 0.5;
	vertices[vertices_index + 2] = 0.0f;

	vertices[vertices_index + 3] = 1.0f;
	vertices[vertices_index + 4] = 1.0f;
	vertices[vertices_index + 5] = 1.0f;

	vertices_index = vertices_index + 6;


	// Set the indices
	indices[indices_index + 0] = 0;
	indices[indices_index + 1] = 1;
	indices[indices_index + 2] = 2;
}

void geom_store::paint_geometry()
{
	// Paint the Triangle
	//tri_shader.Bind();
	//tri_buffers.Bind();

	//// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	//tri_buffers.UnBind();
	//tri_shader.UnBind();


	// Paint the Text
	text_shader.Bind();
	all_labels.paint_text();
	 text_shader.UnBind();
}


