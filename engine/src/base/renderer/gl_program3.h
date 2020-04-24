#pragma once
#include "macros.h"
#include "gl_program.h"

namespace engine
{
	class DLL gl_program3 : public gl_program
	{
	public:
		gl_program3()
		{
			vertex_shader = shader(GL_VERTEX_SHADER, "3d/3d_uber.v");
			fragment_shader = shader(GL_FRAGMENT_SHADER, "3d/3d_uber.f");
		}
	};
}