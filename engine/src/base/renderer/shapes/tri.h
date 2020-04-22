#pragma once

#include "macros.h"

#include <glad/glad.h>

#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"

namespace engine
{
	class DLL tri
	{
		//float verticies[6];
	public:
		uint id, b_id;
		bool active = true;
		bool textured = false;

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