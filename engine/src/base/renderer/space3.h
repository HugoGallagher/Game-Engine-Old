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
#include "base/renderer/light.h"

#include <glad/glad.h>

namespace engine
{
	class DLL space3
	{
	public:
		uint ss_id;

		std::vector<std::shared_ptr<cube>> cubes;
		std::vector<point_light> point_lights;

		gl_program3 d3d_program = gl_program3();

		void init();

		void update();
		void draw(camera& cam);

		std::shared_ptr<cube> create_cube(float s, float xp, float yp, float zp);

		void gen_point_lights();
	};
}