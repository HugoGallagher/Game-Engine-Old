#version 450 core

in vec4 info;

out vec4 colour;

uniform vec4 col;

void main()
{
	colour = col;
}