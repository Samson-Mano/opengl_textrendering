#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include <filesystem>

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<glm\glm.hpp>
#include<glm\vec2.hpp>
#include<glm\vec3.hpp>
#include<glm\vec4.hpp>
#include<glm\mat4x4.hpp>
#include<glm\gtc\type_ptr.hpp>

// https://github.com/Headturna/OpenGL-C---Tutorials/blob/master/Shader.h
// https://github.com/MichaelMoroz/ShaderToy2CPP/blob/master/src/Shaders.cpp

class shader
{
private:
	// Member variables
	unsigned int s_id; // OpenGL program ID
	std::unordered_map<std::string,int> uniform_location_cache;
	std::string loadShaderSource(const char* fileName); // Function to load shader source from file
	unsigned int loadShader(GLenum type, const char* fileName); // Function to load a shader of given type
	void linkProgram(unsigned int vertexShader, unsigned int fragmentShader); // Function to link the shader program
	int get_uniform_location(const std::string uniform_name);
public:
	// Constructors/Destructors
	shader();
	~shader(); // Destructor to clean up OpenGL resources

	void create_shader(const char* vertexFile, const char* fragmentFile);// Function that takes vertex and fragment shader file path
	// Shader usage functions
	void Bind(); // Function to use the shader program
	void UnBind(); // Function to unuse the shader program

	// Uniform setting functions
	void setUniform(std::string name, float X, float Y); // Function to set a 2D float uniform
	void setUniform(std::string name, float X, float Y, float Z); // Function to set a 3D float uniform
	void setUniform(std::string name, float X, float Y, float Z, float W); // Function to set a 4D float uniform
	void setUniform(std::string name, float X); // Function to set a float uniform
	void setUniform(std::string name, int X); // Function to set an integer uniform
	void setUniform(std::string name, glm::mat3 X, bool transpose); // Function to set a mat3 uniform
	void setUniform(std::string name, glm::mat4 X, bool transpose);  // Function to set a mat4 uniform
	void setUniform(std::string name, glm::vec4 X); // Function to set a vec4 uniform
	void setUniform(std::string name, glm::vec3 X); // Function to set a vec3 uniform
	void setUniform(std::string name, glm::vec2 X); // Function to set a vec2 uniform
	void setUniform(int i, unsigned int tid); // Function to set a texture uniform
	unsigned int get_shader_id() const;
};
