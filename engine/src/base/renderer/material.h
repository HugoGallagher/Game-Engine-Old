#pragma once
#include "pch.h"

#include "base/maths/types/vector3.h"

namespace engine
{
	struct material
	{
		vector3 m_col; // General

		vector3 s_col; // Specular
		float s_val, r_val;
	};
}