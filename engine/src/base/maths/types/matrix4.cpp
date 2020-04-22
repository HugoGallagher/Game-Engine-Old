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
			_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f)
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
		data =
		{
			_mm_set_ps(d[0][0], d[0][1], d[0][2], d[0][3]),
			_mm_set_ps(d[1][0], d[1][1], d[1][2], d[1][3]),
			_mm_set_ps(d[2][0], d[2][1], d[2][2], d[2][3]),
			_mm_set_ps(d[3][0], d[3][1], d[3][2], d[3][3]),
		};
		//rdata = d;
	}

	void matrix4::transform(vector3 t, vector3 s, float rx, float ry, float rz)
	{
		data =
		{
			_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f)
		};

		translate(t);
		rotate_x(rx);
		rotate_y(ry);
		rotate_z(rz);
		scale(s);
	}

	void matrix4::translate(vector3& v)
	{
		std::vector<__m128> tdata =
		{
			_mm_set_ps(1.0f, 0.0f, 0.0f, v.x),
			_mm_set_ps(0.0f, 1.0f, 0.0f, v.y),
			_mm_set_ps(0.0f, 0.0f, 1.0f, v.z),
			data[3],
		};
		multiply(*this, tdata);
	}
	void matrix4::scale(vector3& v)
	{
		std::vector<__m128> tdata =
		{
			_mm_set_ps(v.x, 0.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, v.y, 0.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, v.z, 0.0f),
			data[3],
		};
		multiply(*this, tdata);
	}
	void matrix4::translate(float x, float y, float z)
	{
		data =
		{
			_mm_add_ps(data[0], _mm_set_ps(0.0f, 0.0f, 0.0f, x)),
			_mm_add_ps(data[1], _mm_set_ps(0.0f, 0.0f, 0.0f, y)),
			_mm_add_ps(data[2], _mm_set_ps(0.0f, 0.0f, 0.0f, z)),
			data[3],
		};
	}
	void matrix4::scale(float x, float y, float z)
	{
		data =
		{
			_mm_mul_ps(data[0], _mm_set_ps(x, 0.0f, 0.0f, 0.0f)),
			_mm_mul_ps(data[1], _mm_set_ps(0.0f, y, 0.0f, 0.0f)),
			_mm_mul_ps(data[2], _mm_set_ps(0.0f, 0.0f, z, 0.0f)),
			data[3],
		};
	}

	void matrix4::rotate_x(float d)
	{
		std::vector<__m128> tdata =
		{
			_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f),
			_mm_set_ps(0.0f, cos(d), sin(d), 0.0f),
			_mm_set_ps(0.0f, -sin(d), cos(d), 0.0f),
			data[3],
		};
		multiply(*this, tdata);
	}
	void matrix4::rotate_y(float d)
	{
		std::vector<__m128> tdata =
		{
			_mm_set_ps(cos(d), 0.0f, sin(d), 0.0f),
			_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
			_mm_set_ps(-sin(d), 0.0f, cos(d), 0.0f),
			_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f),
		};
		multiply(*this, tdata);
	}
	void matrix4::rotate_z(float d)
	{
		std::vector<__m128> tdata =
		{
			_mm_set_ps(cos(d), -sin(d), 0.0f, 0.0f),
			_mm_set_ps(sin(d), cos(d), 0.0f, 0.0f),
			_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
			data[3],
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

		_mm_store_ps(da[0], data[0]);
		_mm_store_ps(da[1], data[1]);
		_mm_store_ps(da[2], data[2]);
		_mm_store_ps(da[3], data[3]);

		data[0] = _mm_set_ps((2 * n) / r, 0.0f, 0.0f, 0.0f);
		data[1] = _mm_set_ps(0.0f, (2 * n) / t, 0.0f, 0.0f);
		data[2] = _mm_set_ps(0.0f, 0.0f, (2 * n) / (n + f), -n);
		data[3] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	}

	void matrix4::add(matrix4& m1, matrix4& m2)
	{
		for (int i = 0; i < 4; i++)
			this->data[i] = _mm_add_ps(m1.data[i], m2.data[i]);
	}

	void matrix4::multiply(matrix4& m1, matrix4& m2)
	{
		float m1d[4][4];

		_mm_store_ps(m1d[0], m1.data[0]);
		_mm_store_ps(m1d[1], m1.data[1]);
		_mm_store_ps(m1d[2], m1.data[2]);
		_mm_store_ps(m1d[3], m1.data[3]);

		this->data =
		{
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[0][0]), m2.data[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[0][1]), m2.data[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[0][2]), m2.data[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[0][3]), m2.data[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[1][0]), m2.data[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[1][1]), m2.data[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[1][2]), m2.data[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[1][3]), m2.data[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[2][0]), m2.data[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[2][1]), m2.data[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[2][2]), m2.data[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[2][3]), m2.data[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[3][0]), m2.data[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[3][1]), m2.data[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[3][2]), m2.data[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[3][3]), m2.data[0])
			)),
		};
	}
	void matrix4::multiply(matrix4& m1, std::vector<__m128> m2d)
	{
		float m1d[4][4];

		_mm_store_ps(m1d[0], m1.data[0]);
		_mm_store_ps(m1d[1], m1.data[1]);
		_mm_store_ps(m1d[2], m1.data[2]);
		_mm_store_ps(m1d[3], m1.data[3]);

		this->data =
		{
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[0][0]), m2d[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[0][1]), m2d[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[0][2]), m2d[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[0][3]), m2d[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[1][0]), m2d[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[1][1]), m2d[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[1][2]), m2d[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[1][3]), m2d[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[2][0]), m2d[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[2][1]), m2d[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[2][2]), m2d[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[2][3]), m2d[0])
			)),
			_mm_add_ps
			(_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[3][0]), m2d[3]),
				_mm_mul_ps(_mm_set_ps1(m1d[3][1]), m2d[2])
			),_mm_add_ps(
				_mm_mul_ps(_mm_set_ps1(m1d[3][2]), m2d[1]),
				_mm_mul_ps(_mm_set_ps1(m1d[3][3]), m2d[0])
			)),
		};
	}

	void matrix4::update_data()
	{
		float rda[4];
		for (int i = 0; i < 4; i++)
		{
			_mm_store_ps(rda, data[i]);
			rdata.insert(rdata.end(), rda[3]);
			rdata.insert(rdata.end(), rda[2]);
			rdata.insert(rdata.end(), rda[1]);
			rdata.insert(rdata.end(), rda[0]);
			//rdata[i] = { rda[3], rda[2], rda[1], rda[0] };
		}
	}
	void matrix4::update_data_gl()
	{
		float rda[4][4];
		gldata = std::vector<float>();
		gldata.reserve(16);

		_mm_store_ps(rda[0], data[0]);
		_mm_store_ps(rda[1], data[1]);
		_mm_store_ps(rda[2], data[2]);
		_mm_store_ps(rda[3], data[3]);

		for (int i = 0; i < 4; i++)
		{
			gldata.insert(gldata.end(), rda[0][3-i]);
			gldata.insert(gldata.end(), rda[1][3-i]);
			gldata.insert(gldata.end(), rda[2][3-i]);
			gldata.insert(gldata.end(), rda[3][3-i]);
			//rdata[i] = { rda[3], rda[2], rda[1], rda[0] };
		}
	}
}