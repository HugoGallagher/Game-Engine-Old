#include "pch.h"
#include "cube.h"
#include "macros.h"

namespace engine
{
	void cube::create_buffer_data(std::vector<void*> params)
	{
		if (textured)
		{
			t.load();
		}

		n_vs = 36;

		float hl = *(float*)params[0] / 2;

		float verticies[192] =
		{
			-hl, -hl, -hl,  0,  0, -1, 0.0f, 0.0f, // Front
			-hl,  hl, -hl,  0,  0, -1, 0.0f, 1.0f,
			 hl, -hl, -hl,  0,  0, -1, 1.0f, 0.0f,
			 hl,  hl, -hl,  0,  0, -1, 1.0f, 1.0f,

			-hl, -hl,  hl,  0,  0,  1, 0.0f, 0.0f, // Back
			-hl,  hl,  hl,  0,  0,  1, 0.0f, 1.0f,
			 hl, -hl,  hl,  0,  0,  1, 1.0f, 0.0f,
			 hl,  hl,  hl,  0,  0,  1, 1.0f, 1.0f,

			-hl, -hl, -hl, -1,  0,  0, 1.0f, 0.0f, // Left
			-hl,  hl, -hl, -1,  0,  0, 0.0f, 0.0f,
			-hl,  hl,  hl, -1,  0,  0, 0.0f, 1.0f,
			-hl, -hl,  hl, -1,  0,  0, 1.0f, 1.0f,

			 hl, -hl, -hl,  1,  0,  0, 1.0f, 0.0f, // Right
			 hl,  hl, -hl,  1,  0,  0, 0.0f, 0.0f,
			 hl,  hl,  hl,  1,  0,  0, 0.0f, 1.0f,
			 hl, -hl,  hl,  1,  0,  0, 1.0f, 1.0f,

			-hl,  hl, -hl,  0,  1,  0, 0.0f, 0.0f, // Up
			-hl,  hl,  hl,  0,  1,  0, 0.0f, 1.0f,
			 hl,  hl, -hl,  0,  1,  0, 1.0f, 0.0f,
			 hl,  hl,  hl,  0,  1,  0, 1.0f, 1.0f,

			-hl, -hl, -hl,  0, -1,  0, 0.0f, 0.0f, // Down
			-hl, -hl,  hl,  0, -1,  0, 0.0f, 1.0f,
			 hl, -hl, -hl,  0, -1,  0, 1.0f, 0.0f,
			 hl, -hl,  hl,  0, -1,  0, 1.0f, 1.0f,
		};

		uint vis[36] =
		{
			3, 1, 0,
			2, 3, 0,

			4, 5, 7,
			4, 7, 6,

			9, 10, 8,
			11, 8, 10,

			14, 13, 12,
			12, 15, 14,

			19, 17, 16,
			18, 19, 16,

			20, 21, 23,
			20, 23, 22,
		};

		glBindBuffer(GL_ARRAY_BUFFER, b_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vis), vis, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (void*)12);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)24);
		glEnableVertexAttribArray(2);
	}
}