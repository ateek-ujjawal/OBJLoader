#version 410 core
// From Vertex Buffer Object (VBO)
// The only thing that can come 'in', that is
// what our shader reads, the first part of the
// graphics pipeline.
layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoords;
layout(location=2) in vec3 vertexNormals;

// Uniform variables
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Projection; // We'll use a perspective projection

// Pass vertex colors into the fragment shader
out vec2 v_vertexTexCoords;
// out vec3 v_vertexNormals;

void main()
{
  v_vertexTexCoords = texCoords;


  vec4 newPosition = u_Projection * u_ViewMatrix * u_ModelMatrix * vec4(position,1.0f);
                                                                    // Don't forget 'w'
	gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, newPosition.w);
}


