#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"
#include "base/renderer/camera.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector3.h"

namespace engine
{
	class DLL cube
	{
	public:
		uint id, b_id, e_id;
		bool active = true;
		bool textured = false;

		float x, y, z;
		float size;

		vector3 translation;
		vector3 scale = vector3(1.0f, 1.0f, 1.0f);
		float rot_x, rot_y, rot_z;

		std::vector<std::vector<float>> coordinates;
		std::vector<float> colour;

		matrix4 v_matrix, t_matrix, vt_matrix, p_matrix;

		uint colour_loc;
		uint vt_matrix_loc;
		uint p_matrix_loc;

		gl_program program;

		cube(float s, float xp, float yp, float zp, float cs[3], gl_program p);

		void draw(camera& c);

		//cube(const cube& c) : id(c.id), b_id(c.b_id), e_id(c.e_id), program(c.program),
		//                      x(c.x), y(c.y), z(c.z), size(c.size) {}
	};
}