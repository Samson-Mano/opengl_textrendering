#include "app_window.h"

int app_window::window_width = 800;
int app_window::window_height = 600;
bool app_window::isWindowSizeChanging = false;

app_window::app_window()
{
}

app_window::~app_window()
{
}

void app_window::app_render()
{
	// glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{

		// Render OpenGL graphics here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the clear color to black
		glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer


		isWindowSizeChanging = false;

		// Paint the geometry
		geom.paint_geometry();

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}


}

void app_window::init()
{
	// Initialize GLFW
	is_glwindow_success = false;
	if (!glfwInit()) {
		// ShowWindow(GetConsoleWindow(), SW_RESTORE);
		log = "Failed to initialize GLFW";
		// std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Create a window
	window = glfwCreateWindow(window_width, window_height, "Plane Truss Finite Element Solver", nullptr, nullptr);

	if (!window) {
		log = "Failed to create GLFW window";
		// std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		log = "Failed to initialize GLEW";
		// std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}

	//// Maximize the window
	//glfwMaximizeWindow(window);

	// Set viewport size and register framebuffer resize callback
	glfwGetFramebufferSize(window, &window_width, &window_height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Window initialize success
	is_glwindow_success = true;


	framebufferSizeCallback(window, window_width, window_height);

	// Set the geometry
	geom.set_geometry();
}


// Static callback function for framebuffer size changes
// static keyword makes the function a class-level function rather than an instance-level function
// allows it to be used as a callback function for the GLFW library
void app_window::framebufferSizeCallback(GLFWwindow* window, int window_width, int window_height)
{
	// Triggers when the openGL window is resized
	app_window::window_width = window_width;
	app_window::window_height = window_height;

	int max_dim = window_width > window_height ? window_width : window_height;
	int x_offset = (max_dim - window_width) / 2; // Calculate x offset to center the viewport
	int y_offset = (max_dim - window_height) / 2; // Calculate y offset to center the viewport

	// Set the viewport to the maximum dimension and center it at (0, 0)
	glViewport(-x_offset, -y_offset, max_dim, max_dim);

	isWindowSizeChanging = true;
	// glViewport(0, 0, max_size, max_size);
}