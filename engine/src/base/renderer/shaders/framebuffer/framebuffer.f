#version 430 core

in vec2 t_loc;
uniform sampler2D s_tex;

out vec4 colour;

void main()
{
	float o = 0.002;
	vec2 os[9] = vec2[]
	(
		vec2(-o,  o),
		vec2( 0,  o),
		vec2( o,  o),
		vec2(-o,  0),
		vec2( 0,  0),
		vec2( o,  0),
		vec2(-o, -o),
		vec2( 0, -o),
		vec2( o, -o)
	);

	float k[9] = float[]
	(
		 //0.04,  0.16,  0.04,
		 //0.16,  0.25,  0.16,
		 //0.04,  0.16,  0.04

		 -1, -1, -1,
		 -1, 8, -1,
		 -1, -1, -1
	);

	vec3 sum;
	for(int i = 0; i < 9; i++)
	{
		sum += vec3(texture(s_tex, t_loc + os[i])) * k[i];
	}

	colour = vec4(sum, 1);
}