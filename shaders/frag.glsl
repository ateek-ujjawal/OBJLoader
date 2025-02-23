#version 410 core

uniform sampler2D tex;
in vec2 v_vertexTexCoords;
//in vec3 v_vertexNormals;

out vec4 color;

// Entry point of program
void main()
{
	color = texture(tex, v_vertexTexCoords);
}
