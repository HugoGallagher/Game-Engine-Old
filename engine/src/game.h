#pragma once

#include "macros.h"
#include "globals.h"

#include "base/logger.h"
#include "base/events/event.h"
#include "base/events/e_mouse.h"
#include "base/events/e_keyboard.h"
#include "base/events/e_bus.h"

#include "base/window.h"
#include "base/renderer/renderer3.h"
#include "base/input.h"

namespace engine
{
	class DLL game
	{
		logger program_logger;

	public:
		game();
		virtual ~game();

		void run();

		void update();
		void draw();

		void handle_events(e_bus& eb);
	};
}