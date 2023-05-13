#version 330 core

uniform float zoomscale;

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 origin;
layout(location = 2) in vec2 textureCoord;

out vec3 v_textureColor;
out vec2 v_textureCoord;

void main()
{
	// apply zoom scaling and Rotation to model matrix
	mat4 scalingMatrix = mat4(1.0)*zoomscale;
	scalingMatrix[3][3] = 1.0f;
	
	// apply Translation to the final position 
	vec4 finalPosition = scalingMatrix * vec4(position,0.0f,1.0f);

	// apply Translation to the text origin
	vec4 finalTextorigin = scalingMatrix * vec4(origin,0.0f,1.0f);

	// Remove the zoom scale
	vec2 scaled_pt = vec2(finalPosition.x - finalTextorigin.x,finalPosition.y - finalTextorigin.y) / zoomscale;
		
	// Set the final position of the vertex
	gl_Position = vec4(finalPosition.x + scaled_pt.x,finalPosition.y + scaled_pt.y, 0.0f, 1.0f);

	// Calculate texture coordinates for the glyph
	v_textureCoord = textureCoord;
	
	// Pass the texture color to the fragment shader
	v_textureColor = vec3(1.0f,1.0f,1.0f);
}