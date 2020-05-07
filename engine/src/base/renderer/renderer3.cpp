#include "pch.h"
#include "renderer3.h"
#include "macros.h"

#include <glad/glad.h>

#include "base/renderer/opengl/gl_program.h"
#include "base/renderer/opengl/shader.h"

#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

namespace engine
{
	void renderer3::init()
	{
		cam.init();
		space.init();

		fb.init();

		float cs[4] = { 1, 1, 1, 1 };

		//space.create_cube(1, 0, 6, 8);
	}

	void renderer3::update()
	{
		cam.update();
		space.update();
	}

	void renderer3::draw()
	{
		fb.draw_start();

		space.draw(cam);

		fb.draw_end();
	}
}