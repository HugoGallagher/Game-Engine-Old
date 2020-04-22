#pragma once

#include "pch.h"

namespace engine
{
#define E_PRINT_STRING(x) std::stringstream sstring; sstring << x; return sstring.str();

	enum class e_type
	{
		e_mouse_button, e_mouse_scroll, e_mouse_move,
		e_keyboard_key,
	};

	class event
	{
	public:
		e_type type;
		bool handled = false;

		virtual std::string print() const = 0;
		//e_type get_e_type();

		inline bool same_e_type(e_type comparison)
		{
			return type == comparison;
		}
	};
}