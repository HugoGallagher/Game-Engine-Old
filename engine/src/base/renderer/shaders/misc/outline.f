#version 430 core

out vec4 colour;

uniform vec4 outline_col;

void main()
{
	colour = outline_col;
}