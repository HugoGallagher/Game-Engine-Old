#include "pch.h"
#include "renderer.h"
#include "macros.h"

#include <glad/glad.h>

#include "base/renderer/gl_program.h"
#include "base/renderer/shader.h"
#include "base/renderer/shapes/tri.h"
#include "base/renderer/shapes/rect.h"
#include "base/renderer/shapes/cube.h"

namespace engine
{
	void renderer::init()
	{
		glEnable(GL_DEPTH_TEST);
		d2d_program.init();
		d3d_program.init();
		cam.init();

		float cs[4] = { 1, 1, 1, 1 };

		create_cube(1, 20, 15, 30, cs);
	}

	void renderer::update()
	{
		cam.update();
	}

	void renderer::draw()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < tris.size(); i++) // Should eventually loop backwards
		{
			tris[i].draw();
		}
		for (int i = 0; i < rects.size(); i++) // Should eventually loop backwards
		{
			rects[i].draw();
		}
		for (int i = 0; i < cubes.size(); i++) // Should eventually loop backwards
		{
			cubes[i].draw(cam);
		}
	}

	uint renderer::create_tri(float vs[6], float cs[3])
	{
		tri t_tri = tri(vs, cs, d2d_program);
		tris.push_back(t_tri);
		return tris.size() - 1;
	}
	uint renderer::create_rect(float xp, float yp, float w, float h, float cs[3])
	{
		rect t_rect = rect(xp, yp, w, h, cs, d2d_program);
		rects.push_back(t_rect);
		return rects.size() - 1;
	}
	uint renderer::create_cube(float s, float xp, float yp, float zp, float cs[3])
	{
		cube t_cube = cube(s, xp, yp, zp, cs, d3d_program);
		cubes.push_back(t_cube);
		return cubes.size()-1;
	}
	
	void renderer::rotate_x_cube(uint id, float d) { cubes[id].rot_x += d; }
	void renderer::rotate_y_cube(uint id, float d) { cubes[id].rot_y += d; }
	void renderer::rotate_z_cube(uint id, float d) { cubes[id].rot_z += d; }
	void renderer::scale_cube(uint id, vector3 s) { cubes[id].scale = cubes[id].scale + s; }
	void renderer::translate_cube(uint id, vector3 t) { cubes[id].translation = cubes[id].translation + t; }
}