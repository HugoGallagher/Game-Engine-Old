#include "pch.h"

#include "input.h"

namespace engine
{
	namespace input
	{
		mousestate buffer_mousestate = mousestate();
		mousestate current_mousestate = mousestate();
		mousestate previous_mousestate = mousestate();

		keystate buffer_keystate = keystate();
		keystate current_keystate = keystate();
		keystate previous_keystate = keystate();

		void update()
		{
			buffer_mousestate.mouse_delta = buffer_mousestate.mouse_pos - current_mousestate.mouse_pos;

			//std::cout << buffer_mousestate.mouse_delta.x << ", " << buffer_mousestate.mouse_delta.y << std::endl;

			previous_mousestate = current_mousestate;
			current_mousestate = buffer_mousestate;

			previous_keystate = current_keystate;
			current_keystate = buffer_keystate;

			//std::cout << current_keystate.keys_pressed[65] << std::endl;
		}
	}
}