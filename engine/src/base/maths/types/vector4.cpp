#include "pch.h"
#include "macros.h"
#include "vector4.h"

#include "base/maths/types/matrix4.h"

namespace engine
{
	vector4::vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	vector4::vector4(float xp, float yp, float zp, float wp)
	{
		x = xp;
		y = yp;
		z = zp;
		w = wp;
	}
	vector4::vector4(float d[4])
	{
		x = d[0];
		y = d[1];
		z = d[2];
		w = d[3];
	}

	void vector4::multiply(matrix4& m, vector4& v)
	{
		/*m.update_rdata();

		__m128 vector = _mm_set_ps(v.x, v.y, v.z, v.w);

		__m128 r0 = _mm_mul_ps(m.rdata[0], vector);
		__m128 r1 = _mm_mul_ps(m.rdata[1], vector);
		__m128 r2 = _mm_mul_ps(m.rdata[2], vector);
		__m128 r3 = _mm_mul_ps(m.rdata[3], vector);*/

		m.update_data();

		__m128 vector = _mm_set_ps(v.x, v.y, v.z, v.w);

		__m128 r0 = _mm_mul_ps(m.data[0], vector);
		__m128 r1 = _mm_mul_ps(m.data[1], vector);
		__m128 r2 = _mm_mul_ps(m.data[2], vector);
		__m128 r3 = _mm_mul_ps(m.data[3], vector);

		float ra0[4];
		float ra1[4];
		float ra2[4];
		float ra3[4];

		_mm_store_ps(ra0, r0);
		_mm_store_ps(ra1, r1);
		_mm_store_ps(ra2, r2);
		_mm_store_ps(ra3, r3);

		x = ra0[0] + ra0[1] + ra0[2] + ra0[3];
		y = ra1[0] + ra1[1] + ra1[2] + ra1[3];
		z = ra2[0] + ra2[1] + ra2[2] + ra2[3];
		w = ra3[0] + ra3[1] + ra3[2] + ra3[3];
	}
}