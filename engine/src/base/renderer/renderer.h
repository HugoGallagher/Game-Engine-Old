#pragma once

#include "pch.h"
#include "macros.h"

#include "base/renderer/camera.h"
#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"
#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

#include <glad/glad.h>

namespace engine
{
	class DLL renderer
	{
	public:
		std::vector<tri> tris;
		std::vector<rect> rects;
		std::vector<cube> cubes;

		shader d2d_vshader = shader(GL_VERTEX_SHADER, "2d/d2d_vert.v");
		shader d2d_fshader = shader(GL_FRAGMENT_SHADER, "2d/d2d_frag.f");
		gl_program d2d_program = gl_program(d2d_vshader, d2d_fshader);

		shader d3d_vshader = shader(GL_VERTEX_SHADER, "3d/d3d_vert.v");
		shader d3d_fshader = shader(GL_FRAGMENT_SHADER, "3d/d3d_frag.f");
		gl_program d3d_program = gl_program(d3d_vshader, d3d_fshader);

		camera cam;

		void init();
		void update();
		void draw();

		uint create_tri(float vs[6], float cs[3]);
		uint create_rect(float xp, float yp, float w, float h, float cs[3]);
		uint create_cube(float s, float xp, float yp, float zp, float cs[3]);

		void rotate_x_cube(uint id, float d);
		void rotate_y_cube(uint id, float d);
		void rotate_z_cube(uint id, float d);
		void scale_cube(uint id, vector3 s);
		void translate_cube(uint id, vector3 t);
	};
}
