#pragma once
#include "macros.h"

#include "base/renderer/opengl/gl_program.h"

#include <glad/glad.h>

namespace engine
{
	class framebuffer
	{
	public:
		uint id;
		uint c_id;
		uint r_id;

		uint v_id;
		uint b_id;
		uint e_id;

		shader v_shader = shader(GL_VERTEX_SHADER, "framebuffer/framebuffer.v");
		shader f_shader = shader(GL_FRAGMENT_SHADER, "framebuffer/framebuffer.f");
		gl_program program = gl_program(v_shader, f_shader);

		void init()
		{
			program.init();

			glGenFramebuffers(1, &id);
			glBindFramebuffer(GL_FRAMEBUFFER, id);

			glGenTextures(1, &c_id);
			glBindTexture(GL_TEXTURE_2D, c_id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, c_id, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &r_id);
			glBindRenderbuffer(GL_RENDERBUFFER, r_id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, r_id);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glGenBuffers(1, &b_id);
			glGenBuffers(1, &e_id);
			glGenVertexArrays(1, &v_id);

			/*float verticies[16] =
			{
				-1, -1, 1, 0,
				 1, -1, 1, 1,
				-1,  1, 1, 1,
				 1,  1, 1, 1,
			};*/

			float verticies[]
			{
				-1, -1, 0, 0,
				 1, -1, 1, 0,
				 1,  1, 1, 1,

				 1,  1, 1, 1,
				-1,  1, 0, 1,
				-1, -1, 0, 0,
			};

			float vis[6] =
			{
				0, 1, 2,
				0, 2, 3,
			};

			glBindVertexArray(v_id);

			glBindBuffer(GL_ARRAY_BUFFER, b_id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void draw_start()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, id);
			glClearColor(0.25, 0.25, 0.25, 0.25);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
		}

		void draw_end()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(program.id);
			glBindVertexArray(v_id);
			glDisable(GL_DEPTH_TEST);
			glBindTexture(GL_TEXTURE_2D, c_id);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			glBindFramebuffer(GL_FRAMEBUFFER, id);
		}
	};
}