#include "pch.h"

#include "logger.h"

namespace engine
{
	logger::logger()
	{
	}

	void logger::log(levels l, const std::string& text)
	{
		if (l == info and this->c_level[0] == true)
		{
			std::cout << "INFO: " << text << std::endl;
		}
		else if (l == warn and this->c_level[1] == true)
		{
			std::cout << "WARN: " << text << std::endl;
		}
		else if (l == crit and this->c_level[2] == true)
		{
			std::cout << "CRIT: " << text << std::endl;
		}
	}

	void logger::change_level(levels l, bool new_value)
	{
		this->c_level[l] = new_value;
	}

	void logger::quick_log(levels l, const std::string& text)
	{
		switch (l)
		{
		case info:
			std::cout << "INFO: " << text << std::endl;
			break;
		case warn:
			std::cout << "WARN: " << text << std::endl;
			break;
		case crit:
			std::cout << "CRIT: " << text << std::endl;
			break;
		}
	}
}