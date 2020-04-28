#include "pch.h"
#include "renderer3.h"
#include "macros.h"

#include <glad/glad.h>

#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"
#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

namespace engine
{
	void renderer3::init()
	{
		glEnable(GL_DEPTH_TEST);
		cam.init();
		space.init();

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
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		space.draw(cam);
	}
}