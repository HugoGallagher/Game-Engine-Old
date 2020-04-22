#pragma once

#include "pch.h"

namespace engine
{
	template<typename T>
	inline T lerp(T v1, T v2, float i);

	DLL inline float degrees(float r);
	DLL inline float radians(float r);
}