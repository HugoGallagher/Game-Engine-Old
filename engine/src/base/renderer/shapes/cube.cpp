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

		float verticies[24] =
		{
			-hl, -hl,  -hl,
			-hl, -hl,   hl,
			-hl,  hl,  -hl,
			-hl,  hl,   hl,
			 hl, -hl,  -hl,
			 hl, -hl,   hl,
			 hl,  hl,  -hl,
			 hl,  hl,   hl,
		};

		uint verts[36] =
		{
			0, 1, 2,
			3, 1, 2,
			3, 6, 7,
			3, 2, 6,
			6, 7, 5,
			6, 5, 4,
			0, 1, 5,
			0, 5, 4,
			0, 2, 4,
			6, 2, 4,
			3, 1, 5,
			5, 3, 7,
		};

		glGenBuffers(1, &b_id);
		glGenBuffers(1, &e_id);
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void cube::draw(camera& c)
	{
		t_matrix.transform(translation, scale, rot_x, rot_y, rot_z);

		vt_matrix.multiply(c.v_matrix, t_matrix);
		vt_matrix.update_data_gl();

		glUseProgram(program.id);
		glBindVertexArray(id);

		colour_loc = glGetUniformLocation(program.id, "col");
		glUniform4f(colour_loc, colour[0], colour[1], colour[2], colour[3]);

		vt_matrix_loc = glGetUniformLocation(program.id, "vt_matrix");
		p_matrix_loc = glGetUniformLocation(program.id, "p_matrix");

		glUniformMatrix4fv(vt_matrix_loc, 1, GL_FALSE, &vt_matrix.gldata[0]);
		glUniformMatrix4fv(p_matrix_loc, 1, GL_FALSE, &c.p_matrix.gldata[0]);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(colour_loc, 0, 0, 0, 1);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}