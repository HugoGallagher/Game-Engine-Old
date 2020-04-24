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
		d2d_program.init();
		d3d_program.init();
		cam.init();

		float cs[4] = { 1, 1, 1, 1 };

		create_cube(1, 0, 6, 8, cs);
	}

	void renderer3::update()
	{
		cam.update();
	}

	void renderer3::draw()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(d3d_program.id);

		for (int i = 0; i < cubes.size(); i++) // Should eventually loop backwards
		{
			cubes[i].draw(d3d_program, cam);
		}
	}

	uint renderer3::create_cube(float s, float xp, float yp, float zp, float cs[3])
	{
		cube t_cube = cube(cs);
		std::vector<float> test = { s };
		t_cube.init(xp, yp, zp, std::vector<float>(1, s));
		cubes.push_back(t_cube);
		return cubes.size()-1;
	}
	
	void renderer3::rotate_x_cube(uint id, float d) { cubes[id].rotation.x += d; }
	void renderer3::rotate_y_cube(uint id, float d) { cubes[id].rotation.y += d; }
	void renderer3::rotate_z_cube(uint id, float d) { cubes[id].rotation.z += d; }
	void renderer3::scale_cube(uint id, vector3 s) { cubes[id].scale = cubes[id].scale + s; }
	void renderer3::translate_cube(uint id, vector3 t) { cubes[id].position = cubes[id].position + t; }
}