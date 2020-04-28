#pragma once

#include "base/maths/types/vector3.h"

namespace engine
{
	class light
	{
	public:
		vector3 col;
		float str;
	};

	class point_light : public light
	{
	public:
		vector3 pos;
	};

	class dir_light : public light
	{
	public:
		vector3 dir;
	};
}