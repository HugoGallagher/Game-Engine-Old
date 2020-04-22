#pragma once
#include "pch.h"
#include "macros.h"

#include "base/maths/types/vector3.h"
#include "base/maths/types/matrix4.h"

namespace engine
{
	class DLL vector4
	{
	public:
		float x, y, z, w;

		vector4();
		vector4(float xp, float yp, float zp, float wp);
		vector4(float d[4]);
		vector4(vector3 v);

		void multiply(matrix4& m, vector4& v);
	};
}