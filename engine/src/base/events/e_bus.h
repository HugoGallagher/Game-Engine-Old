#pragma once

#include "macros.h"

#include "base/events/event.h"
#include "base/events/e_mouse.h"
#include "base/events/e_keyboard.h"

namespace engine
{
	struct DLL e_bus
	{
		const int dvl = 10; // default_vector_length

		std::vector<e_mouse_button> e_mb;
		std::vector<e_mouse_scroll> e_ms;
		std::vector<e_mouse_move> e_mm;
		std::vector<e_keyboard_key> e_kk;

		e_bus()
		{
			//e_mouse_button e = e_mouse_button(0, 0, 1.0f, 1.0f);

			e_mb.reserve(dvl);
			e_ms.reserve(dvl);
			e_mm.reserve(dvl);
			e_kk.reserve(dvl);
		}

		static e_bus& event_bus()
		{
			e_bus eb;
			return eb;
		}
	};

	extern e_bus eb;
}