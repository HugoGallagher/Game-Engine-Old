#pragma once

#include "macros.h"

#include <glad/glad.h>

#include "base/renderer/opengl/shader.h"

namespace engine
{
	class DLL gl_program
	{
	public:
		uint id;
		shader vertex_shader, fragment_shader;

		gl_program() {}
		gl_program(shader& v, shader& f) : vertex_shader(v), fragment_shader(f) {}
		
		void init();
	};
}