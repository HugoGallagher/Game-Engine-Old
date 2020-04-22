#pragma once

#include "base/events/event.h"

namespace engine
{
	class e_mouse_button : public event
	{
	public:
		e_type type = e_type::e_mouse_button;

		int button_pressed, action;
		float x_loc, y_loc;

		e_mouse_button(int b, int a, float x, float y) : button_pressed(b), action(a), x_loc(x), y_loc(y) {}

		std::string print() const override
		{
			E_PRINT_STRING("Button " << button_pressed << " state changed (" << action << ") at (" << x_loc << ", " << y_loc << ")");
		}
	};

	class e_mouse_scroll : public event
	{
	public:
		e_type type = e_type::e_mouse_scroll;

		float distance_scrolled;
		float x_loc, y_loc;

		e_mouse_scroll(float s, float x, float y) : distance_scrolled(s), x_loc(x), y_loc(y) {}

		std::string print() const override
		{
			E_PRINT_STRING(distance_scrolled << " scrolled at (" << x_loc << ", " << y_loc << ")");
		}
	};

	class e_mouse_move : public event
	{
	public:
		e_type type = e_type::e_mouse_move;

		float x_loc, y_loc;

		e_mouse_move(float x, float y) : x_loc(x), y_loc(y) {}

		std::string print() const override
		{
			E_PRINT_STRING("Mouse moved to (" << x_loc << ", " << y_loc << ")");
		}
	};
}