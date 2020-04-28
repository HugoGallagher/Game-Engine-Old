#include "space3.h"

#include "base/renderer/light.h"

namespace engine
{
	void space3::init()
	{
		glGenBuffers(1, &ss_id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ss_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ss_id);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		point_light pl1;
		pl1.pos = { 0, 10, 7 };
		pl1.str = 5;
		pl1.col = { 1, 1, 1 };
		point_light pl2;
		pl2.pos = { 0, -10, 0 };
		pl2.str = 10;
		pl2.col = { 1, 1, 1 };

		point_lights.push_back(pl1);
		point_lights.push_back(pl2);
		gen_point_lights();

		d3d_program.init();
	}

	void space3::update() {}

	void space3::draw(camera& cam)
	{
		glUseProgram(d3d_program.id);

		for (int i = 0; i < cubes.size(); i++)
		{
			cubes[i]->draw(d3d_program, cam);
		}
	}

	std::shared_ptr<cube> space3::create_cube(float s, float xp, float yp, float zp)
	{
		cube t_cube = cube();
		std::vector<float> test = { s };
		t_cube.init(xp, yp, zp, std::vector<void*>(1, &s));

		std::shared_ptr<cube> t_cube_ptr = std::make_shared<cube>(t_cube);
		cubes.push_back(t_cube_ptr);
		return t_cube_ptr;
	}

	void space3::gen_point_lights()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ss_id);
		std::vector<float> float_point_lights(0);

		for (int i = 0; i < point_lights.size(); i++)
		{
			float_point_lights.push_back(point_lights[i].pos.x);
			float_point_lights.push_back(point_lights[i].pos.y);
			float_point_lights.push_back(point_lights[i].pos.z);
			
			float_point_lights.push_back(point_lights[i].col.x);
			float_point_lights.push_back(point_lights[i].col.y);
			float_point_lights.push_back(point_lights[i].col.z);

			float_point_lights.push_back(point_lights[i].str);
		}
		glBufferData(GL_SHADER_STORAGE_BUFFER, float_point_lights.size() * 4, &float_point_lights[0], GL_STATIC_READ);
	}
}