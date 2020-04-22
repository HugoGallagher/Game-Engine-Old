#pragma once

#include "base/events/event.h"

namespace engine
{
	class e_keyboard_key : public event
	{
	public:
		e_type type = e_type::e_keyboard_key;

		int key_pressed, scancode, action;

		e_keyboard_key(int k, int s, int a) : key_pressed(k), scancode(s), action(a) {}

		std::string print() const override
		{
			E_PRINT_STRING(key_pressed << " (" << scancode << ") pressed");
		}
	};
}