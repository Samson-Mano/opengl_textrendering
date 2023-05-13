#include "shader.h"

shader::shader()
	:s_id(0), uniform_location_cache()
{

}

// Constructor that takes vertex and fragment shader file names
void shader::create_shader(const char* vertexFile, const char* fragmentFile)
{
	// Load and compile the vertex shader
	unsigned int vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

	// Load and compile the fragment shader
	unsigned int fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

	// Link the shader program
	linkProgram(vertexShader, fragmentShader);

	// Delete the individual shaders as they are no longer needed after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Destructor
shader::~shader()
{
	glDeleteProgram(this->s_id);
}

unsigned int shader::get_shader_id() const
{
	return s_id;
}

// Load shader source from file and return as string
std::string shader::loadShaderSource(const char* fileName)
{
	std::string temp = ""; // Temporary string to store each line of the shader source
	std::string src = ""; // Final string to store the entire shader source

	std::ifstream in_file; // Input file stream for reading from file

	//std::filesystem::path original_dir = std::filesystem::current_path();
	//std::filesystem::current_path("C:/Users/HFXMSZ/OneDrive - LR/ Documents/Programming/Other programs/Cpp_projects/Truss_static_analysis_cpp/Truss_static_analysis_cpp/src/geometry_store/shaders/");

	// Open the file with the given file name
	in_file.open(fileName);

	// std::filesystem::current_path(original_dir);

	if (in_file.is_open()) // Check if file was successfully opened
	{
		while (std::getline(in_file, temp)) // Read each line from file
			src += temp + "\n"; // Append each line to the final shader source string with a newline character
	}
	else
	{
		std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n"; // Print error message if file could not be opened
	}

	in_file.close(); // Close the file

	//// Replace the #version directive in the shader source with a default version number
	//src.replace(src.find("#version"), 12, "#version 330"); // Replace with desired version number

	return src; // Return the final shader source string
}

// Load shader source from file and compile shader
unsigned int shader::loadShader(GLenum type,const char* fileName)
{
	char infoLog[512];
	int success;

	unsigned int shader = glCreateShader(type); // Create a shader object of given type
	std::string str_src = this->loadShaderSource(fileName); // Load shader source from file
	const char* src = str_src.c_str(); // Convert shader source to GLchar array
	glShaderSource(shader, 1, &src, NULL); // Set shader source
	glCompileShader(shader); // Compile shader source

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success); // Check shader compilation status
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog); // Get shader compilation error log
		std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
		std::cout << infoLog << "\n"; // Print shader compilation error log
	}

	return shader; // Return compiled shader object
}


// Link vertex and fragment shaders to create shader program
void shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	char infoLog[512];
	int success;

	this->s_id = glCreateProgram(); // Create a shader program object

	glAttachShader(this->s_id, vertexShader); // Attach vertex shader to shader program

	glAttachShader(this->s_id, fragmentShader); // Attach fragment shader to shader program

	glLinkProgram(this->s_id); // Link shader program

	glGetProgramiv(this->s_id, GL_LINK_STATUS, &success); // Check shader program linking status
	if (!success)
	{
		glGetProgramInfoLog(this->s_id, 512, NULL, infoLog); // Get shader program linking error log
		std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
		std::cout << infoLog << "\n"; // Print shader program linking error log
	}

	glUseProgram(0); // Unbind shader program
}

int shader::get_uniform_location(const std::string uniform_name)
{
	// Return the uniform location
	if (uniform_location_cache.find(uniform_name) != uniform_location_cache.end())
	{
		return uniform_location_cache[uniform_name];
	}

	// Uniform is not found in the hashtable ? Dictionary
	// So add it to the dictionary
	int uniform_location_id = glGetUniformLocation(this->s_id, uniform_name.c_str());
	uniform_location_cache[uniform_name] = uniform_location_id;

	return uniform_location_id;
}

// Bind and un-Bind 
void shader::Bind()
{
	glUseProgram(this->s_id); // Use the shader program
}

void shader::UnBind()
{
	glUseProgram(0); // Un-use the shader program
}

//Set uniform functions
void shader::setUniform(std::string name, float X, float Y) // Function to set a 2D float uniform
{
	Bind(); // Use the shader program

	unsigned int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name
	glUniform2f(uniformLocation, X, Y); // Set the 2D float uniform with the provided values for X and Y

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, float X, float Y, float Z) // Function to set a 3D float uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name
	glUniform3f(uniformLocation, X, Y, Z); // Set the 3D float uniform with the provided values for X, Y and Z

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, float X, float Y, float Z, float W) // Function to set a 4D float uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name
	glUniform4f(uniformLocation, X, Y, Z,W); // Set the 4D float uniform with the provided values for X, Y and Z

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, float X) // Function to set a float uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name
	glUniform1f(uniformLocation, X); // Set the 1D float uniform with the provided value for X

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, int X) // Function to set an integer uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name
	glUniform1i(uniformLocation, X); // Set the 1D int uniform with the provided value for X

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, glm::mat3 X, bool transpose) // Function to set a mat3 uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name

	if (transpose)
	{
		glUniformMatrix3fv(uniformLocation, 1, GL_TRUE, glm::value_ptr(glm::transpose(X))); // Set the mat3 uniform with the transpose of the provided matrix
	}
	else
	{
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(X)); // Set the mat3 uniform with the provided matrix
	}

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, glm::mat4 X, bool transpose) // Function to set a mat4 uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name

	if (transpose)
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, glm::value_ptr(glm::transpose(X))); // Set the mat4 uniform with the transpose of the provided matrix
	}
	else
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(X)); // Set the mat4 uniform with the provided matrix
	}

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, glm::vec4 X) // Function to set a vec4 uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name

	glUniform4fv(uniformLocation, 1, glm::value_ptr(X)); // Set the vec4 uniform with the provided value for X

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, glm::vec3 X) // Function to set a vec3 uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name

	glUniform3fv(uniformLocation, 1, glm::value_ptr(X)); // Set the vec3 uniform with the provided value for X

	UnBind(); // Un-use the shader program
}

void shader::setUniform(std::string name, glm::vec2 X) // Function to set a vec2 uniform
{
	Bind(); // Use the shader program

	int uniformLocation = glGetUniformLocation(this->s_id, name.c_str()); // Get the uniform location using the provided name

	glUniform2fv(uniformLocation, 1, glm::value_ptr(X)); // Set the vec2 uniform with the provided value for X

	UnBind(); // Un-use the shader program
}

void shader::setUniform(int i, unsigned int tid) // Function to set a texture uniform
{
	Bind(); // Use the shader program

	// Activate the texture unit i
	glActiveTexture(GL_TEXTURE0 + i);

	// Bind the texture with the provided texture ID (tid) to the active texture unit
	glBindTexture(GL_TEXTURE_2D, tid);

	// Set the uniform value to the texture unit index i
	glUniform1i(glGetUniformLocation(this->s_id, "textureSampler"), i);

	UnBind(); // Un-use the shader program
}