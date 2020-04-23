#version 450 core

in vec3 o_pos;
in vec3 normal;

out vec4 colour;

uniform vec3 v_pos;
uniform vec3 l_pos;
uniform vec4 l_col;
uniform vec4 o_col;

void main()
{
	float specular = 1.0;
	float roughness = 0.0;

	vec3 l_dir = normalize(l_pos - o_pos);
	float d_val = max(dot(l_dir, normal), 0);
	float a_val = 0.15;
	
	vec3 v_dir = normalize(o_pos - v_pos);
	vec3 r_dir = normalize(reflect(l_dir, normal));
	float s_val = specular * pow(max(dot(v_dir, r_dir), 0), 256 - roughness);

	float l_val = s_val + d_val + a_val;
	colour = o_col * l_val;
}