#pragma once
#include "pch.h"
#include "macros.h"

#include <glad/glad.h>

namespace engine
{
	class DLL shader
	{
	public:
		uint id, type;

		std::string path;
		std::string code;

		shader() {}
		shader(uint t, const std::string& p) : type(t), path(p) {}

		void init();
	};
}