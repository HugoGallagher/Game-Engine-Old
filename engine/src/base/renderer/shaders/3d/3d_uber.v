#version 430 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 n;
layout(location=2) in vec2 t_pos;

out vec3 o_pos;
out vec3 normal;
out vec2 t_loc;

uniform mat4 m_matrix;
uniform mat4 n_matrix;
uniform mat4 v_matrix;
uniform mat4 pv_matrix;

void main()
{
	o_pos = (m_matrix * vec4(pos, 1)).xyz;
	normal = mat3(transpose(inverse(n_matrix))) * n;
	t_loc = t_pos;
	gl_Position = pv_matrix * m_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}