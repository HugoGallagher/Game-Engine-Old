#version 450 core

layout(location=0) in vec3 pos;

uniform mat4 vt_matrix;
uniform mat4 p_matrix;

void main()
{
	gl_Position = p_matrix * vt_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}