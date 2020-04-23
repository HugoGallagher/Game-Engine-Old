#include "pch.h"
#include "cube.h"
#include "macros.h"

namespace engine
{
	cube::cube(float s, float xp, float yp, float zp, float cs[3], gl_program p) : x(xp), y(yp), size(s), program(p)
	{
		//p_matrix.update_data_gl();

		//coordinates = { xp, yp, xp + w, yp, xp + w, yp + h, xp, yp + h };
		colour = { cs[0] / 255, cs[1] / 255, cs[2] / 255, cs[3] / 255, 255 };

		x = xp;
		y = yp;
		z = zp;

		translation = vector3(x, y, z);

		float hl = s / 2;

		/*coordinates.push_back({ -hl, -hl, -hl });
		coordinates.push_back({ -hl, -hl,  hl });
		coordinates.push_back({ -hl,  hl, -hl });
		coordinates.push_back({ -hl,  hl,  hl });
		coordinates.push_back({  hl, -hl, -hl });
		coordinates.push_back({  hl, -hl,  hl });
		coordinates.push_back({  hl,  hl, -hl });
		coordinates.push_back({  hl,  hl,  hl });*/

		/*float verticies[24] =
		{
			-1.0f, -1.0f, -1.0f
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			 hl, -hl, -hl,
			 hl, -hl,  hl,
			 hl,  hl, -hl,
			 hl,  hl,  hl,
		};*/

		/*uint verts[36] =
		{
			0, 1, 3,
			0, 3, 2,
			0, 1, 4,
			1, 4, 5,
			1, 2, 5,
			2, 5, 6,
			2, 3, 6,
			3, 6, 7,
			3, 7, 4,
			0, 4, 7,
			4, 5, 7,
			4, 7, 6,
		};*/

		//float verticies[24] =
		//{
		//	-hl, -hl, -hl,
		//	-hl, -hl,  hl,
		//	-hl,  hl, -hl,
		//	-hl,  hl,  hl,
		//	 hl, -hl, -hl,
		//	 hl, -hl,  hl,
		//	 hl,  hl, -hl,
		//	 hl,  hl,  hl,
		//};

		//uint verts[36] =
		//{
		//	0, 1, 2,
		//	3, 1, 2,
		//	3, 6, 7,
		//	3, 2, 6,
		//	6, 7, 5,
		//	6, 5, 4,
		//	0, 1, 5,
		//	0, 5, 4,
		//	0, 2, 4,
		//	6, 2, 4,
		//	3, 1, 5,
		//	5, 3, 7,
		//};

		float verticies[144] =
		{
			-hl, -hl, -hl,  0,  0, -1, // Front
			-hl,  hl, -hl,  0,  0, -1,
			 hl, -hl, -hl,  0,  0, -1,
			 hl,  hl, -hl,  0,  0, -1,

			-hl, -hl,  hl,  0,  0,  1, // Back
			-hl,  hl,  hl,  0,  0,  1,
			 hl, -hl,  hl,  0,  0,  1,
			 hl,  hl,  hl,  0,  0,  1,

			-hl, -hl, -hl, -1,  0,  0, // Left
			-hl,  hl, -hl, -1,  0,  0,
			-hl,  hl,  hl, -1,  0,  0,
			-hl, -hl,  hl, -1,  0,  0,

			 hl, -hl, -hl,  1,  0,  0, // Right
			 hl,  hl, -hl,  1,  0,  0,
			 hl,  hl,  hl,  1,  0,  0,
			 hl, -hl,  hl,  1,  0,  0,

			-hl,  hl, -hl,  0,  1,  0, // Up
			-hl,  hl,  hl,  0,  1,  0,
			 hl,  hl, -hl,  0,  1,  0,
			 hl,  hl,  hl,  0,  1,  0,

			-hl, -hl, -hl,  0, -1,  0, // Down
			-hl, -hl,  hl,  0, -1,  0,
			 hl, -hl, -hl,  0, -1,  0,
			 hl, -hl,  hl,  0, -1,  0,
		};

		uint vis[36] =
		{
			0, 1, 3,
			0, 3, 2,

			4, 5, 7,
			4, 7, 6,

			8, 9, 10,
			8, 11, 10,

			12, 13, 14,
			12, 15, 14,

			16, 17, 19,
			16, 19, 18,

			20, 21, 23,
			20, 23, 22,
		};

		glGenBuffers(1, &b_id);
		glGenBuffers(1, &e_id);
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vis), vis, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void cube::draw(camera& cam)
	{
		m_matrix.transform(translation, scale, rot_x, rot_y, rot_z);
		m_matrix.update_data_gl();
		n_matrix = m_matrix;
		n_matrix.update_data_gl();

		glUseProgram(program.id);
		glBindVertexArray(id);

		uint colour_loc = glGetUniformLocation(program.id, "o_col");
		uint l_colour_loc = glGetUniformLocation(program.id, "l_col");
		uint l_position_loc = glGetUniformLocation(program.id, "l_pos");
		uint v_position_loc = glGetUniformLocation(program.id, "v_pos");
		
		uint m_matrix_loc = glGetUniformLocation(program.id, "m_matrix");
		uint n_matrix_loc = glGetUniformLocation(program.id, "n_matrix");
		uint pv_matrix_loc = glGetUniformLocation(program.id, "pv_matrix");
		uint v_matrix_loc = glGetUniformLocation(program.id, "v_matrix");

		glUniform4f(colour_loc, colour[0], colour[1], colour[2], colour[3]);
		glUniform4f(l_colour_loc, 1, 1, 1, 1);
		glUniform3f(l_position_loc, 0, 6, 8);
		glUniform3f(v_position_loc, -cam.position.x, -cam.position.y, -cam.position.z);

		glUniformMatrix4fv(m_matrix_loc, 1, GL_FALSE, &m_matrix.gldata[0]);
		glUniformMatrix4fv(n_matrix_loc, 1, GL_FALSE, &n_matrix.gldata[0]);
		glUniformMatrix4fv(pv_matrix_loc, 1, GL_FALSE, &cam.pv_matrix.gldata[0]);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}