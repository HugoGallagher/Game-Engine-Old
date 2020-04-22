#pragma once

#include "pch.h"

#include "macros.h"

namespace engine
{
	class DLL logger
	{
		bool c_level[3] = { true, true, true };

	public:
		static enum levels { info, warn, crit };

	public:
		//static void format_text(std::string text, std::vector<char> args);

		logger();

		void log(levels l, const std::string& text);

		void change_level(levels l, bool new_value);

		static void quick_log(levels l, const std::string& text);
	};
}