#pragma once
#include "pch.h"
#include "macros.h"

#include "base/renderer/opengl/gl_program.h"
#include "base/renderer/opengl/gl_program2.h"
#include "base/renderer/opengl/gl_program3.h"
#include "base/renderer/opengl/shader.h"
#include "base/renderer/opengl/framebuffer.h"

#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"
#include "base/renderer/light.h"
#include "base/renderer/camera.h"

#include <glad/glad.h>

namespace engine
{
	class DLL space3
	{
	public:
		uint ss_id;

		std::vector<std::shared_ptr<cube>> cubes;
		std::vector<point_light> point_lights;
		std::vector<dir_light> dir_lights;

		gl_program3 d3d_program = gl_program3(); // Default 3D

		shader dv_shader = shader(GL_VERTEX_SHADER, "3d/3d_uber.v");
		shader of_shader = shader(GL_FRAGMENT_SHADER, "misc/outline.v");
		gl_program3 o3d_program = gl_program3(); // Outline 3D

		void init();

		void update();
		void draw(camera& cam);

		void uniforms(camera& cam);

		std::shared_ptr<cube> create_cube(float s, float xp, float yp, float zp);

		void gen_lights();
	};
}