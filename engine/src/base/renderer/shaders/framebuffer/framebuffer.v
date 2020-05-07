#version 430 core

layout(location=0) in vec2 v_pos;
layout(location=1) in vec2 t_pos;

out vec2 t_loc;

void main()
{
	t_loc = t_pos;
	gl_Position = vec4(v_pos, 0, 1);
}