#include "shape3.h"

namespace engine
{
	void shape3::init(float xp, float yp, float zp, std::vector<void*> params)
	{
		position = vector3(xp, yp, zp);

		glGenBuffers(1, &b_id);
		glGenBuffers(1, &e_id);
		glGenVertexArrays(1, &id);

		glBindVertexArray(id);

		this->create_buffer_data(params);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void shape3::draw(gl_program3& prog, camera& cam)
	{
		m_matrix.transform(position, scale, rotation);
		m_matrix.update_data_gl();
		n_matrix = m_matrix;
		n_matrix.update_data_gl();
		glBindVertexArray(id);

		uniforms(prog, cam);

		glDrawElements(GL_TRIANGLES, n_vs, GL_UNSIGNED_INT, 0);
	}

	void shape3::uniforms(gl_program3& prog, camera& cam)
	{
		uint l_colour_loc = glGetUniformLocation(prog.id, "l_col");
		uint l_position_loc = glGetUniformLocation(prog.id, "l_pos");
		uint v_position_loc = glGetUniformLocation(prog.id, "v_pos");

		uint m_matrix_loc = glGetUniformLocation(prog.id, "m_matrix");
		uint n_matrix_loc = glGetUniformLocation(prog.id, "n_matrix");
		uint pv_matrix_loc = glGetUniformLocation(prog.id, "pv_matrix");
		uint v_matrix_loc = glGetUniformLocation(prog.id, "v_matrix");

		glUniform4f(l_colour_loc, 1, 1, 1, 1);
		glUniform3f(l_position_loc, 0, 6, 8);
		glUniform3f(v_position_loc, -cam.position.x, -cam.position.y, -cam.position.z);

		glUniformMatrix4fv(m_matrix_loc, 1, GL_FALSE, &m_matrix.gldata[0]);
		glUniformMatrix4fv(n_matrix_loc, 1, GL_FALSE, &n_matrix.gldata[0]);
		glUniformMatrix4fv(pv_matrix_loc, 1, GL_FALSE, &cam.pv_matrix.gldata[0]);

		uint m_m_col_loc = glGetUniformLocation(prog.id, "m.m_col");
		uint m_s_col_loc = glGetUniformLocation(prog.id, "m.s_col");
		uint m_s_val_loc = glGetUniformLocation(prog.id, "m.s_val");
		uint m_r_val_loc = glGetUniformLocation(prog.id, "m.r_val");

		glUniform3f(m_m_col_loc, m.m_col.x / 255, m.m_col.y / 255, m.m_col.z / 255);
		glUniform3f(m_s_col_loc, m.s_col.x / 255, m.s_col.y / 255, m.s_col.z / 255);
		glUniform1f(m_s_val_loc, m.s_val);
		glUniform1f(m_r_val_loc, m.r_val);

		uint s_texture_loc = glGetUniformLocation(prog.id, "s_tex");
		glUniform1f(s_texture_loc, 0.5);

		if (textured)
			t.bind();
	}
}