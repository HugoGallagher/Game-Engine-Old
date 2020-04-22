#pragma once
#include "macros.h"

#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector3.h"

namespace engine
{
	class DLL rect
	{
	public:
		uint id, b_id, e_id;
		bool active = true;
		bool textured = false;

		float x, y;
		float width, height;

		std::vector<float> coordinates;
		std::vector<float> colour;

		matrix4 v_matrix, t_matrix, vt_matrix, p_matrix;

		uint colour_loc;
		uint vt_matrix_loc;
		uint p_matrix_loc;

		gl_program program;

		rect(float xp, float yp, float w, float h, float c[3], gl_program p);

		void draw();
	};
}