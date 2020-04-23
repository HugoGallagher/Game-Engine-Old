#include "camera.h"

namespace engine
{
	void camera::init() { p_matrix.projection(16.0f / 9.0f, FOV); }
	
	void camera::update()
	{
		delta_speed = speed * delta_time;

		// Temporary code

		if (input::current_keystate.keys_pressed[86] || input::current_keystate.keys_pressed[82] || input::current_keystate.keys_pressed[64] || input::current_keystate.keys_pressed[67])
		{
			vector3 tm = vector3(1, 0, 0);
			tm.x = cos(rotation.x);
			tm.z = sin(rotation.x);

			if (input::current_keystate.keys_pressed[86])
			{
				position.x -= tm.z * delta_speed;
				position.z -= tm.x * delta_speed;
			}
			if (input::current_keystate.keys_pressed[82])
			{
				position.x += tm.z * delta_speed;
				position.z += tm.x * delta_speed;
			}

			if (input::current_keystate.keys_pressed[64])
			{
				position.x += tm.x * delta_speed;
				position.z -= tm.z * delta_speed;
			}
			if (input::current_keystate.keys_pressed[67])
			{
				position.x -= tm.x * delta_speed;
				position.z += tm.z * delta_speed;
			}
		}

		if (input::current_keystate.keys_pressed[31])
		{
			position.y -= delta_speed;
		}
		if (input::current_keystate.keys_pressed[66])
		{
			position.y += delta_speed;
		}

		//

		vector2 delta = input::current_mousestate.mouse_delta / 500;
		rotation = rotation + delta;
		//std::cout << rotation.x << std::endl;
		v_matrix = matrix4();
		v_matrix.rotate_x(rotation.y);
		v_matrix.rotate_y(-rotation.x);
		v_matrix.translate(position);
		v_matrix.update_data_gl();

		pv_matrix.multiply(p_matrix, v_matrix);
		pv_matrix.update_data_gl();
	}
}