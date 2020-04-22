#pragma once

#include "macros.h"

#include "matrix4.h"

namespace engine
{
	class DLL vector2
	{
		//matrix4 fjkulerbjfhk;

	public:
		float x, y;

		vector2() : x(0.0f), y(0.0f) {}
		vector2(float xd, float yd) : x(xd), y(yd) {}

		inline vector2 operator+(vector2& v) { return vector2(this->x + v.x, this->y + v.y); }
		inline vector2 operator-(vector2& v) { return vector2(this->x - v.x, this->y - v.y); }
		inline vector2 operator*(vector2& v) { return vector2(this->x * v.x, this->y * v.y); }
		inline vector2 operator/(vector2& v) { return vector2(this->x / v.x, this->y / v.y); }

		inline vector2 operator/(float f) { return vector2(this->x / f, this->y / f); }

		inline void normalise(vector2& v);

		inline float magnitude();
		inline float dot(vector2& v);
		inline float angle(vector2& v);
	};
}

