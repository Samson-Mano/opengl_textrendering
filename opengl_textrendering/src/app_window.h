#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "buffers/gBuffers.h"
#include "geom_store.h"

class app_window
{
public:
	bool is_glwindow_success = false;
	static int window_width;
	static int window_height;
	static bool isWindowSizeChanging;
	const char* log = "";

	// Constructor and Destructor
	app_window();
	~app_window();

	// Functions
	void init();
	void app_render();
	static void framebufferSizeCallback(GLFWwindow* window, int window_width, int window_height);
private:
	GLFWwindow* window = nullptr;
	geom_store geom;
};
