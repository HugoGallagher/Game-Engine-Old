#pragma once

#include "pch.h"
#include "macros.h"

#include "base/renderer/camera.h"
#include "base/renderer/gl_program.h"
#include "base/renderer/gl_program2.h"
#include "base/renderer/gl_program3.h"
#include "base/renderer/shader.h"
#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

#include <glad/glad.h>

namespace engine
{
	class DLL renderer3
	{
	public:
		std::vector<cube> cubes;

		gl_program2 d2d_program = gl_program2();

		gl_program3 d3d_program = gl_program3();

		camera cam;

		void init();
		void update();
		void draw();

		uint create_cube(float s, float xp, float yp, float zp, float cs[3]);

		void rotate_x_cube(uint id, float d);
		void rotate_y_cube(uint id, float d);
		void rotate_z_cube(uint id, float d);
		void scale_cube(uint id, vector3 s);
		void translate_cube(uint id, vector3 t);
	};
}
