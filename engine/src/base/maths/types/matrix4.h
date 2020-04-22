#pragma once
#include "pch.h"
#include "macros.h"

#include "base/maths/types/matrix.h"
#include "base/maths/types/vector3.h"

namespace engine
{
	class DLL matrix4
	{
	public:
		std::vector<std::vector<float>> data;
		__m128 rdata[4];
		std::vector<float> gldata;

		matrix4();
		matrix4(std::vector<std::vector<float>>& d);

		void transform(vector3 t, vector3 s, float rx, float ry, float rz);

		void translate(vector3& v);
		void scale(vector3& v);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void rotate_x(float d);
		void rotate_y(float d);
		void rotate_z(float d);

		void add(matrix4& m1, matrix4& m2);
		void multiply(matrix4& m1, matrix4& m2);
		void multiply(matrix4& m1, std::vector<std::vector<float>> m2);

		void projection(float ar, float fov);

		void update_data();
		void update_rdata();
		void update_data_gl();

		/*matrix4 operator+(matrix4& m)
		{
			std::vector<std::vector<float>> d(4);
			for (int i = 0; i < 4; i++)
			{
				float rs[4];
				__m128 r = _mm_add_ps(this->data[i], m.data[i]);
				_mm_store_ps(rs, r);
				d[i] = std::vector<float>(rs, rs + 4);
			}
			return matrix4(d);
		}*/
	};
}