#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/gl_program.h"
#include "base/renderer/gl_program3.h"
#include "base/renderer/shader.h"
#include "base/renderer/camera.h"
#include "base/renderer/material.h"

#include "base/maths/types/matrix4.h"
#include "base/maths/types/vector4.h"
#include "base/maths/types/vector3.h"

namespace engine
{
	class DLL shape3
	{
	public:
		uint id, b_id, e_id;
		bool active = true;
		bool textured = false;
		uint n_vs;

		std::vector<float> colour; // Temp

		vector3 position;
		vector3 scale = vector3(1.0f, 1.0f, 1.0f);
		vector3 rotation;
		matrix4 m_matrix, n_matrix;

		material m;

		shape3() {}
		void init(float xp, float yp, float zp, std::vector<float> params);

		void draw(gl_program3& prog, camera& cam);

		virtual void create_buffer_data(std::vector<float> params) {}

		void uniforms(gl_program3& prog, camera& cam);
	};
}