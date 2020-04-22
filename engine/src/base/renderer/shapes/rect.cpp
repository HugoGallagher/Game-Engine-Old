#include "pch.h"
#include "rect.h"
#include "macros.h"

namespace engine
{
	rect::rect(float xp, float yp, float w, float h, float c[3], gl_program p) : x(xp), y(yp), width(w), height(h), program(p)
	{
		p_matrix.projection(16.0f / 9.0f, 60.0f);
		//p_matrix.update_data_gl();

		coordinates = { xp, yp, xp + w, yp, xp + w, yp + h, xp, yp + h };
		colour = { c[0] / 255, c[1] / 255, c[2] / 255, c[3] / 255, 255 };

		x = xp;
		y = yp;

		t_matrix.translate(0.5f, -(y / (HEIGHT / 2)), 0.0f);

		colour_loc = glGetUniformLocation(program.id, "col");
		//p_matrix_loc = glGetUniformLocation(program.id, "p_matrix");

		float verticies[12] =
		{
			-1.0f, 1.0f, 1.0f,
			w / (WIDTH / 2) - 1.0f, 1.0f, 5.0f,
			w / (WIDTH / 2) - 1.0f, 1.0f - h / (HEIGHT / 2), 5.0f,
			-1.0f, 1.0f - h / (HEIGHT / 2), 1.0f,
		};
		uint verts[6] =
		{
			0, 1, 2,
			0, 3, 2,
		};

		glGenBuffers(1, &b_id);
		glGenBuffers(1, &e_id);
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, 48, verticies, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 48, verts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void rect::draw()
	{
		vt_matrix.multiply(v_matrix, t_matrix);
		vt_matrix.update_data_gl();
		p_matrix.update_data_gl();

		glUseProgram(program.id);
		glUniform4f(colour_loc, colour[0], colour[1], colour[2], colour[3]);
		glBindVertexArray(id);

		vector4 tv0 = vector4(-0.5f, 0.5f, 2.0f, 1.0f);
		vector4 tv1 = vector4(0.5f, -0.5f, 2.0f, 1.0f);
		vector4 tv2 = vector4(-0.5f, -0.5f, 2.0f, 1.0f);
		vector4 tv3 = vector4(0.5f, 0.5f, 2.0f, 1.0f);

		tv0.multiply(vt_matrix, tv0);
		tv0.multiply(p_matrix, tv0);
		tv1.multiply(vt_matrix, tv1);
		tv1.multiply(p_matrix, tv1);
		tv2.multiply(vt_matrix, tv2);
		tv2.multiply(p_matrix, tv2);
		tv3.multiply(vt_matrix, tv3);
		tv3.multiply(p_matrix, tv3);

		vt_matrix_loc = glGetUniformLocation(program.id, "vt_matrix");
		p_matrix_loc = glGetUniformLocation(program.id, "p_matrix");

		glUniformMatrix4fv(vt_matrix_loc, 1, GL_FALSE, &vt_matrix.gldata[0]);
		glUniformMatrix4fv(p_matrix_loc, 1, GL_FALSE, &p_matrix.gldata[0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}