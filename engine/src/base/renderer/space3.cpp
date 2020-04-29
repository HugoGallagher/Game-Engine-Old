#include "space3.h"

#include "base/renderer/light.h"

namespace engine
{
	void space3::init()
	{
		glGenBuffers(1, &ss_id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ss_id);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ss_id);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		point_light pl1;
		pl1.pos = { 0, 10, 7 };
		pl1.col = { 1, 1, 1 };
		pl1.str = 5;
		point_light pl2;
		pl2.pos = { 0, -10, 0 };
		pl2.col = { 1, 1, 1 };
		pl2.str = 10;

		dir_light dl1;
		dl1.dir = { 0, -1, -0.25 };
		dl1.col = { 1, 1, 1 };
		dl1.str = 1;

		point_lights.push_back(pl1);
		point_lights.push_back(pl2);

		dir_lights.push_back(dl1);

		gen_lights();

		d3d_program.init();
	}

	void space3::update() {}

	void space3::draw(camera& cam)
	{
		glUseProgram(d3d_program.id);

		uniforms(cam);

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

	void space3::uniforms(camera& cam)
	{
		uint v_position_loc = glGetUniformLocation(d3d_program.id, "v_pos");
		glUniform3f(v_position_loc, -cam.position.x, -cam.position.y, -cam.position.z);

		uint pv_matrix_loc = glGetUniformLocation(d3d_program.id, "pv_matrix");
		glUniformMatrix4fv(pv_matrix_loc, 1, GL_FALSE, &cam.pv_matrix.gldata[0]);
	}

	void space3::gen_lights()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ss_id);
		std::vector<float> float_lights(0);

		for (int i = 0; i < point_lights.size(); i++)
		{
			float_lights.push_back(0);

			float_lights.push_back(point_lights[i].pos.x);
			float_lights.push_back(point_lights[i].pos.y);
			float_lights.push_back(point_lights[i].pos.z);

			float_lights.push_back(point_lights[i].col.x);
			float_lights.push_back(point_lights[i].col.y);
			float_lights.push_back(point_lights[i].col.z);

			float_lights.push_back(point_lights[i].str);
		}
		for (int i = 0; i < dir_lights.size(); i++)
		{
			float_lights.push_back(1);

			float_lights.push_back(dir_lights[i].dir.x);
			float_lights.push_back(dir_lights[i].dir.y);
			float_lights.push_back(dir_lights[i].dir.z);

			float_lights.push_back(dir_lights[i].col.x);
			float_lights.push_back(dir_lights[i].col.y);
			float_lights.push_back(dir_lights[i].col.z);

			float_lights.push_back(dir_lights[i].str);
		}
		glBufferData(GL_SHADER_STORAGE_BUFFER, float_lights.size() * 4, &float_lights[0], GL_STATIC_READ);
	}
}