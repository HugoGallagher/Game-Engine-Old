#pragma once
#include "macros.h"
#include "gl_program.h"

namespace engine
{
	class DLL gl_program2 : public gl_program
	{
	public:
		gl_program2()
		{
			vertex_shader = shader(GL_VERTEX_SHADER, "2d/2d_uber.v");
			fragment_shader = shader(GL_FRAGMENT_SHADER, "2d/2d_uber.f");
		}
	};
}