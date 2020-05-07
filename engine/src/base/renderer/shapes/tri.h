#pragma once
#include "macros.h"

#include "base/renderer/shapes/shape2.h"

#include "base/renderer/opengl/gl_program.h"
#include "base/renderer/opengl/shader.h"

#include <glad/glad.h>

namespace engine
{
	class DLL tri : private shape2
	{
	public:
		std::vector<float> coordinates;
		std::vector<float> colour;

		uint coordinates_loc;
		uint colour_loc;

		gl_program program;

		tri(float vs[6], float c[3], gl_program p);

		void draw();

		//void set_position(float vs[3]);
	};
}