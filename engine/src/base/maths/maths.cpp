#include "pch.h"
#include "macros.h"
#include "globals.h"

#include "maths.h"

namespace engine
{
	template<typename T>
	T lerp(T v1, T v2, float i) { return v1 + (v2 - v1) * i; }

	DLL float degrees(float r)
	{
		return r / PI * 180;
	}
	DLL float radians(float r)
	{
		return r / 180 * PI;
	}
}