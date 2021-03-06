#version 430 core

struct light
{
	float id;
	float var[3]; // Use differes for types of lights
	float col[3];
	float str;
};

layout(binding = 1, std430) buffer light_buffer
{
	light lights[];
};

struct material
{
	vec3 m_col; // Material colour
	vec3 s_col; // Specular colour
	float s_val; // Specular
	float r_val; // Roughness
	float t_val; // Transparency
	
	bool textured;
	sampler2D tex; // Texture
	float t_str; // Texture strength
};

uniform material m;

in vec3 o_pos;
in vec3 normal;
in vec2 t_loc;

out vec4 colour;

uniform vec3 v_pos;
uniform vec4 o_col;

vec3 point_light_val(light l, material mat, vec3 v_dir, vec3 n, vec3 o_pos)
{
	vec3 pl_pos = vec3(l.var[0], l.var[1], l.var[2]);
	vec3 pl_col = vec3(l.col[0], l.col[1], l.col[2]);

	vec3 l_dir = pl_pos - o_pos;
	float l_dis = l_dir.length();
	float l_int = 1 / (l_dis * l_dis);

	l_dir = normalize(l_dir);
	float d_val = max(dot(l_dir, n), 0) * l_int * l.str;
	vec3 r_dir = normalize(reflect(l_dir, n));
	float s_val = mat.s_val * pow(max(dot(v_dir, r_dir), 0), (1 - mat.r_val) * 256);

	return mat.m_col * pl_col * d_val + m.s_col * s_val;
}
vec3 dir_light_val(light l, material mat, vec3 v_dir, vec3 n, vec3 o_pos)
{
	vec3 dl_dir = vec3(l.var[0], l.var[1], l.var[2]);
	vec3 dl_col = vec3(l.col[0], l.col[1], l.col[2]);

	return max(dot(-dl_dir, normal), 0) * m.m_col * dl_col * l.str;
}

void main()
{
	float a_val = 0.15;
	vec3 v_dir = normalize(o_pos - v_pos);

	vec3 l_val;

	for (int i = 0; i < lights.length()+1; i++)
	{
		if (lights[i].id == 0)
		{
			l_val += point_light_val(lights[i], m, v_dir, normal, o_pos);
		}
		if (lights[i].id == 1)
		{
			l_val += dir_light_val(lights[i], m, v_dir, normal, o_pos);
		}
	}

	l_val += m.m_col * a_val;

	if (m.textured)
	{
		vec4 m_val = vec4(l_val, m.t_val);

		colour = m_val * (1 - m.t_str) + m_val * texture(m.tex, t_loc) * m.t_str;
	}
	else
	{
		colour = vec4(l_val, m.t_val);
	}
}