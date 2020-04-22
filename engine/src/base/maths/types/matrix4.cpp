#include "matrix4.h"
#include "pch.h"
#include "macros.h"

#include "base/maths/types/matrix.h"

namespace engine
{
	matrix4::matrix4()
	{
		data =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		/*rdata =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};*/
	}
	matrix4::matrix4(std::vector<std::vector<float>>& d)
	{
		data = d;
		//rdata = d;
	}

	void matrix4::transform(vector3 t, vector3 s, float rx, float ry, float rz)
	{
		data =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};

		translate(t);
		rotate_x(rx);
		rotate_y(ry);
		rotate_z(rz);
		scale(s);
	}

	void matrix4::translate(vector3& v)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ 1.0f, 0.0f, 0.0f, data[0][3] + v.x },
			{ 0.0f, 1.0f, 0.0f, data[1][3] + v.y },
			{ 0.0f, 0.0f, 1.0f, data[2][3] + v.z },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}
	void matrix4::scale(vector3& v)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ data[0][0] * v.x, 0.0f, 0.0f, 0.0f },
			{ 0.0f, data[1][1] * v.y, 0.0f, 0.0f },
			{ 0.0f, 0.0f, data[2][2] * v.z, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}
	void matrix4::translate(float x, float y, float z)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ 1.0f, 0.0f, 0.0f, data[0][3] + x },
			{ 0.0f, 1.0f, 0.0f, data[1][3] + y },
			{ 0.0f, 0.0f, 1.0f, data[2][3] + z },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}
	void matrix4::scale(float x, float y, float z)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ data[0][0] * x, 0.0f, 0.0f, 0.0f },
			{ 0.0f, data[1][1] * y, 0.0f, 0.0f },
			{ 0.0f, 0.0f, data[2][2] * z, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}

	void matrix4::rotate_x(float d)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, cos(d), sin(d), 0.0f },
			{ 0.0f, -sin(d), cos(d), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}
	void matrix4::rotate_y(float d)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ cos(d), 0.0f, sin(d), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ -sin(d), 0.0f, cos(d), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}
	void matrix4::rotate_z(float d)
	{
		std::vector<std::vector<float>> tdata =
		{
			{ cos(d), -sin(d), 0.0f, 0.0f },
			{ sin(d), cos(d), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		multiply(*this, tdata);
	}

	void matrix4::projection(float ar, float fov)
	{
		float n = 0.5f;
		float f = 200.0f;

		float t = atan(fov / 2) * n;
		float r = t * ar;

		float da[4][4];

		data =
		{
			{ (2 * n) / r, 0.0f, 0.0f, 0.0f },
			{ 0.0f, (2 * n) / t, 0.0f, 0.0f },
			{ 0.0f, 0.0f, (2 * n) / (n + f), -n },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
		};
	}

	void matrix4::add(matrix4& m1, matrix4& m2)
	{
		m1.update_rdata();
		m2.update_rdata();

		for (int i = 0; i < 4; i++)
			rdata[i] = _mm_add_ps(m1.rdata[i], m2.rdata[i]);

		update_data();
	}

	void matrix4::multiply(matrix4& m1, matrix4& m2)
	{
		m1.update_rdata();
		m2.update_rdata();

		for (int i = 0; i < 4; i++)
		{
			rdata[i] =
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1.data[i][3]), m2.rdata[3]),
				_mm_mul_ps(_mm_set_ps1(m1.data[i][2]), m2.rdata[2])
			), _mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1.data[i][1]), m2.rdata[1]),
				_mm_mul_ps(_mm_set_ps1(m1.data[i][0]), m2.rdata[0])
			));
		}

		update_data();
	}
	void matrix4::multiply(matrix4& m1, std::vector<std::vector<float>> m2)
	{
		m1.update_rdata();

		__m128 m2d[4];
		for (int i = 0; i < 4; i++)
		{
			m2d[i] = _mm_set_ps(m2[i][0], m2[i][1], m2[i][2], m2[i][3]);
		}

		for (int i = 0; i < 4; i++)
		{
			rdata[i] =
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1.data[i][3]), m2d[3]),
				_mm_mul_ps(_mm_set_ps1(m1.data[i][2]), m2d[2])
			), _mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1.data[i][1]), m2d[1]),
				_mm_mul_ps(_mm_set_ps1(m1.data[i][0]), m2d[0])
			));
		}

		update_data();
	}

	void matrix4::update_data()
	{
		float rd[4];
		for (int i = 0; i < 4; i++)
		{
			_mm_store_ps(rd, rdata[i]);
			data[i] = { rd[3], rd[2], rd[1], rd[0] };
		}
	}
	void matrix4::update_rdata()
	{
		for (int i = 0; i < 4; i++)
		{
			rdata[i] = _mm_set_ps(data[i][0], data[i][1], data[i][2], data[i][3]);
		}
	}
	void matrix4::update_data_gl()
	{
		gldata = std::vector<float>();
		gldata.reserve(16);

		for (int i = 0; i < 4; i++)
		{
			gldata.insert(gldata.end(), data[0][i]);
			gldata.insert(gldata.end(), data[1][i]);
			gldata.insert(gldata.end(), data[2][i]);
			gldata.insert(gldata.end(), data[3][i]);
			//rdata[i] = { rda[3], rda[2], rda[1], rda[0] };
		}
	}
}