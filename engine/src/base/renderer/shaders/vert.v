#version 450 core

layout(location=0) in vec3 pos;

out vec4 info;

uniform mat4 vt_matrix;
uniform mat4 p_matrix;

void main()
{
	info = p_matrix * vec4(pos.x, pos.y, pos.z+3, 1.0);
	gl_Position = p_matrix * vt_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}