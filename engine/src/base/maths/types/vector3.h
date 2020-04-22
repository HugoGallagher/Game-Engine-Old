#pragma once

#include "macros.h"

namespace engine
{
	class DLL vector3
	{
	public:
		float x, y, z;

		vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		vector3(float xd, float yd, float zd) : x(xd), y(yd), z(zd) {}

		inline void normalise(vector3& v);

		inline vector3 cross(vector3& v1, vector3& v2);

		inline vector3 operator+(vector3& v) { return vector3(this->x + v.x, this->y + v.y, this->z + v.z); }
		inline vector3 operator-(vector3& v) { return vector3(this->x - v.x, this->y - v.y, this->z - v.z); }
		inline vector3 operator*(vector3& v) { return vector3(this->x * v.x, this->y * v.y, this->z * v.z); }
		inline vector3 operator/(vector3& v) { return vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

		inline vector3 operator+=(vector3& v) { return vector3(this->x + v.x, this->y + v.y, this->z + v.z); }

		inline vector3 operator*(float f) { return vector3(this->x * f, this->y * f, this->z * f); }
	};
}
