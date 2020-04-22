#pragma once

#include "macros.h"

#include "base/events/event.h"
#include "base/events/e_mouse.h"
#include "base/events/e_keyboard.h"
#include "base/events/e_bus.h"

#include "base/maths/types/vector2.h"

namespace engine
{
	namespace input
	{
		enum mouse_buttons
		{
			mb_leftclick,
			mb_rightclick,
			mb_middleclick,
			mb_forward,
			mb_back,
		};

		struct mousestate
		{
			std::vector<bool> buttons_pressed = std::vector<bool>(5);
			vector2 mouse_pos = vector2(0, 0);
			vector2 mouse_delta = vector2(0, 0);
		};
		struct keystate
		{
			std::vector<bool> keys_pressed = std::vector<bool>(128); //Eventually convert to 4 ints
		};

		extern mousestate buffer_mousestate;
		extern mousestate current_mousestate;
		extern mousestate previous_mousestate;

		extern keystate buffer_keystate;
		extern keystate current_keystate;
		extern keystate previous_keystate;

		void update();

		inline bool update_mousepos(float nx, float ny) { buffer_mousestate.mouse_pos.x = nx; buffer_mousestate.mouse_pos.y = ny; return true; }
		inline bool update_mousebuttons(mouse_buttons b, bool nv) { buffer_mousestate.buttons_pressed[b] = nv; return true; }
		
		inline bool update_keys(char k, bool nv) { buffer_keystate.keys_pressed[k-1] = nv; return true; }

		inline bool button_down(mouse_buttons mb) { return current_mousestate.buttons_pressed[mb]; }
		inline bool button_clicked(mouse_buttons mb) { return current_mousestate.buttons_pressed[mb] and !previous_mousestate.buttons_pressed[mb]; }
		inline vector2 mouse_delta() { return vector2(current_mousestate.mouse_pos - previous_mousestate.mouse_pos); }

		inline bool key_down(char k) { return current_keystate.keys_pressed[k]; }
		inline bool key_typed(char k) { return current_keystate.keys_pressed[k] and !previous_keystate.keys_pressed[k]; }
	};
}