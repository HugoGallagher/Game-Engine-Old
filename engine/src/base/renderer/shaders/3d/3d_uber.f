#version 430 core

struct point_light
{
	float pos[3];
	float col[3];
	float str;
};

layout(binding = 5, std430) buffer light_buffer
{
	point_light point_lights[];
};

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
in vec2 t_loc;

out vec4 colour;

uniform vec3 v_pos;
uniform vec3 l_pos;
uniform vec4 l_col;
uniform vec4 o_col;

uniform sampler2D tex;
uniform float s_tex;

vec3 point_light_ds_val(point_light pl, material mat, vec3 v_dir, vec3 n, vec3 o_pos)
{
	float a_val = 0.15;
	vec3 pl_pos = vec3(pl.pos[0], pl.pos[1], pl.pos[2]);
	vec3 pl_col = vec3(pl.col[0], pl.col[1], pl.col[2]);

	vec3 l_dir = pl_pos - o_pos;
	float l_dis = l_dir.length();
	float l_int = 1 / (l_dis * l_dis);

	l_dir = normalize(l_dir);
	float d_val = max(dot(l_dir, n), 0) * l_int * pl.str;
	vec3 r_dir = normalize(reflect(l_dir, n));
	float s_val = mat.s_val * pow(max(dot(v_dir, r_dir), 0), (1 - mat.r_val) * 256);

	return mat.m_col * pl_col * d_val + m.s_col * s_val + mat.m_col * a_val;
}

void main()
{
	//pl.pos = vec3(0, 10, 0);

	vec3 v_dir = normalize(o_pos - v_pos);
	//colour = texture(tex, t_loc);
	//colour = vec4(t_loc.xy, 0, 1);

	vec3 l_val;

	for (int i = 0; i < point_lights.length()+1; i++)
	{
		l_val += point_light_ds_val(point_lights[i], m, v_dir, normal, o_pos);
	}
	colour = vec4(l_val, 1);
}