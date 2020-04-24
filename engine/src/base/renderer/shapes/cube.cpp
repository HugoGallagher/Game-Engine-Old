#include "pch.h"
#include "cube.h"
#include "macros.h"

namespace engine
{
	void cube::create_buffer_data(std::vector<float> params)
	{
		n_vs = 36;

		float hl = params[0] / 2;

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

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vis), vis, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
		glEnableVertexAttribArray(1);
	}
}