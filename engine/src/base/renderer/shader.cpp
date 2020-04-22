#include "pch.h"
#include "macros.h"
#include "shader.h"

namespace engine
{
	void shader::init()
	{
		std::ifstream shader_file;
		std::string line;
		std::string full_path = SHADER_PATH + path;

		shader_file.open(full_path, std::ios::in);
		while (std::getline(shader_file, line))
		{
			code.append(line);
			code.append("\n");
		}
		code.append("\0");
		shader_file.close();

		const char* c_code = code.c_str();

		id = glCreateShader(type);
		glShaderSource(id, 1, &c_code, NULL);
		glCompileShader(id);

		int s;
		char e[256];
		glGetShaderiv(id, GL_COMPILE_STATUS, &s);
		if (!s)
		{
			glGetShaderInfoLog(id, 256, NULL, e);
			std::cout << "Shader error: Compilation failed:\n\t" << e << std::endl;
		}
	}
}