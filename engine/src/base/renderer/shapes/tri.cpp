#include "pch.h"
#include "tri.h"
#include "macros.h"

namespace engine
{
	tri::tri(float vs[6], float c[3], gl_program p) : program(p)
	{
		coordinates = { vs[0], vs[1], vs[2], vs[3], vs[4], vs[5] };
		colour = { c[0] / 255, c[1] / 255, c[2] / 255, 255 };

		//coordinates_loc = glGetUniformLocation(program.id, "pos");
		colour_loc = glGetUniformLocation(program.id, "col");

		float verticies[6] = // Abstract
		{
			vs[0] / (WIDTH / 2) - 1.0f, -(vs[1] / (HEIGHT / 2) - 1.0f),
			vs[2] / (WIDTH / 2) - 1.0f, -(vs[3] / (HEIGHT / 2) - 1.0f),
			vs[4] / (WIDTH / 2) - 1.0f, -(vs[5] / (HEIGHT / 2) - 1.0f),
		};

		//float colour[4] = { c[0], c[1], c[2], c[3] };

		glGenBuffers(1, &b_id);
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, 24, verticies, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 24, (void*)8);

		glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);

		//glUniform4f(colour_loc, 1.0f, 5.0f, 0.0f, 1.0f);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void tri::draw()
	{
		glUseProgram(program.id);
		glUniform4f(colour_loc, colour[0], colour[1], colour[2], colour[3]);
		glBindVertexArray(id);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}