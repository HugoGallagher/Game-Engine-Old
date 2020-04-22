#include "pch.h"
#include "macros.h"
#include "gl_program.h"

namespace engine
{
	void gl_program::init()
	{
		vertex_shader.init();
		fragment_shader.init();

		id = glCreateProgram();
		glAttachShader(id, vertex_shader.id);
		glAttachShader(id, fragment_shader.id);
		glLinkProgram(id);

		int s;
		char e[256];
		glGetProgramiv(id, GL_LINK_STATUS, &s);
		if (!s)
		{
			glGetShaderInfoLog(id, 256, NULL, e);
			std::cout << "Program error: Linking failed:\n\t" << e << std::endl;
		}

		glDeleteShader(vertex_shader.id);
		glDeleteShader(fragment_shader.id);
	}
}