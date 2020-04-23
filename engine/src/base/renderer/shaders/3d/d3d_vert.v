#version 450 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 n;

out vec3 o_pos;
out vec3 normal;

uniform mat4 m_matrix;
uniform mat4 n_matrix;
uniform mat4 v_matrix;
uniform mat4 pv_matrix;

void main()
{
	o_pos = (m_matrix * vec4(pos, 1)).xyz;
	normal = mat3(transpose(inverse(n_matrix))) * n;
	gl_Position = pv_matrix * m_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}