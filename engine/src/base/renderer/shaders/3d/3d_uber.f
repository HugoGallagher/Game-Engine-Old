#version 450 core

struct material
{
	vec3 m_col; // Material colour
	vec3 s_col; // Specular colour
	float s_val; // Specular
	float r_val; // Roughness
};

uniform material m;

in vec3 o_pos;
in vec3 normal;

out vec4 colour;

uniform vec3 v_pos;
uniform vec3 l_pos;
uniform vec4 l_col;
uniform vec4 o_col;

void main()
{
	vec3 l_dir = normalize(l_pos - o_pos);
	float d_val = max(dot(l_dir, normal), 0);
	float a_val = 0.15;
	
	vec3 v_dir = normalize(o_pos - v_pos);
	vec3 r_dir = normalize(reflect(l_dir, normal));
	float s_val = m.s_val * pow(max(dot(v_dir, r_dir), 0), (1 - m.r_val) * 256);

	colour = vec4((m.m_col * (d_val + a_val)) + m.s_col * s_val, 1);
}