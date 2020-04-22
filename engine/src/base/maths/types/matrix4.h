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
		std::vector<__m128> data;
		std::vector<float> rdata;
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
		void multiply(matrix4& m1, std::vector<__m128> m2d);

		void projection(float ar, float fov);

		void update_data();
		void update_data_gl();

		matrix4 operator+(matrix4& m)
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
		}

		/*matrix4 operator+(matrix4& m)
		{
			return matrix4
			({
				{ this->data[0][0] + m.data[0][0], this->data[0][1] + m.data[0][1], this->data[0][2] + m.data[0][2], this->data[0][3] + m.data[0][3] },
				{ this->data[1][0] + m.data[1][0], this->data[1][1] + m.data[1][1], this->data[1][2] + m.data[1][2], this->data[1][3] + m.data[1][3] },
				{ this->data[2][0] + m.data[2][0], this->data[2][1] + m.data[2][1], this->data[2][2] + m.data[2][2], this->data[2][3] + m.data[2][3] },
				{ this->data[3][0] + m.data[3][0], this->data[3][1] + m.data[3][1], this->data[3][2] + m.data[3][2], this->data[3][3] + m.data[3][3] }
			});
		}
		matrix4 operator-(matrix4& m)
		{
			return matrix4
			({
				{ this->data[0][0] - m.data[0][0], this->data[0][1] - m.data[0][1], this->data[0][2] - m.data[0][2], this->data[0][3] - m.data[0][3] },
				{ this->data[1][0] - m.data[1][0], this->data[1][1] - m.data[1][1], this->data[1][2] - m.data[1][2], this->data[1][3] - m.data[1][3] },
				{ this->data[2][0] - m.data[2][0], this->data[2][1] - m.data[2][1], this->data[2][2] - m.data[2][2], this->data[2][3] - m.data[2][3] },
				{ this->data[3][0] - m.data[3][0], this->data[3][1] - m.data[3][1], this->data[3][2] - m.data[3][2], this->data[3][3] - m.data[3][3] }
			});
		}

		matrix4 operator*(matrix4& m)
		{
			return matrix4
			({
				{ this->data[0][0] * m.data[0][0] + this->data[0][1] * m.data[1][0] + this->data[0][2] * m.data[2][0] + this->data[0][3] * m.data[3][0], this->data[0][0] * m.data[0][1] + this->data[0][1] * m.data[1][1] + this->data[0][2] * m.data[2][1] + this->data[0][3] * m.data[3][1], this->data[0][0] * m.data[0][2] + this->data[0][1] * m.data[1][2] + this->data[0][2] * m.data[2][2] + this->data[0][3] * m.data[3][2], this->data[0][0] * m.data[0][3] + this->data[0][1] * m.data[1][3] + this->data[0][2] * m.data[2][3] + this->data[0][3] * m.data[3][3] },
				{ this->data[1][0] * m.data[0][0] + this->data[1][1] * m.data[1][0] + this->data[1][2] * m.data[2][0] + this->data[1][3] * m.data[3][0], this->data[1][0] * m.data[0][1] + this->data[1][1] * m.data[1][1] + this->data[1][2] * m.data[2][1] + this->data[1][3] * m.data[3][1], this->data[1][0] * m.data[0][2] + this->data[1][1] * m.data[1][2] + this->data[1][2] * m.data[2][2] + this->data[1][3] * m.data[3][2], this->data[1][0] * m.data[0][3] + this->data[1][1] * m.data[1][3] + this->data[1][2] * m.data[2][3] + this->data[1][3] * m.data[3][3] },
				{ this->data[2][0] * m.data[0][0] + this->data[2][1] * m.data[1][0] + this->data[2][2] * m.data[2][0] + this->data[2][3] * m.data[3][0], this->data[2][0] * m.data[0][1] + this->data[2][1] * m.data[1][1] + this->data[2][2] * m.data[2][1] + this->data[2][3] * m.data[3][1], this->data[2][0] * m.data[0][2] + this->data[2][1] * m.data[1][2] + this->data[2][2] * m.data[2][2] + this->data[2][3] * m.data[3][2], this->data[2][0] * m.data[0][3] + this->data[2][1] * m.data[1][3] + this->data[2][2] * m.data[2][3] + this->data[2][3] * m.data[3][3] },
				{ this->data[3][0] * m.data[0][0] + this->data[3][1] * m.data[1][0] + this->data[3][2] * m.data[2][0] + this->data[3][3] * m.data[3][0], this->data[3][0] * m.data[0][1] + this->data[3][1] * m.data[1][1] + this->data[3][2] * m.data[2][1] + this->data[3][3] * m.data[3][1], this->data[3][0] * m.data[0][2] + this->data[3][1] * m.data[1][2] + this->data[3][2] * m.data[2][2] + this->data[3][3] * m.data[3][2], this->data[3][0] * m.data[0][3] + this->data[3][1] * m.data[1][3] + this->data[3][2] * m.data[2][3] + this->data[3][3] * m.data[3][3] }
			});
		}*/
	};
}