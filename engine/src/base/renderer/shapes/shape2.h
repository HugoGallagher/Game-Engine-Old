#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/opengl/gl_program2.h"
#include "base/renderer/opengl/shader.h"

#include "base/renderer/camera.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector2.h"

namespace engine
{
	class DLL shape2
	{
	public:
		uint id, b_id, e_id;
		bool active = true;
		bool textured = false;

		vector2 translation;
		vector2 scale = vector2(1.0f, 1.0f);
		vector2 rotation;
		matrix4 m_matrix, n_matrix;

		gl_program2 program;

		shape2() {}
		shape2(float xp, float yp, gl_program p);

		void draw(camera& cam);
	};
}