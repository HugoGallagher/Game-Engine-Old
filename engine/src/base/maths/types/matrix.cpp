#include "matrix.h"
#include "pch.h"
#include "macros.h"

namespace engine
{
	std::vector<std::vector<float>> matrix::imatrix =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f, },
		{ 0.0f, 1.0f, 0.0f, 0.0f, },
		{ 0.0f, 0.0f, 1.0f, 0.0f, },
		{ 0.0f, 0.0f, 0.0f, 1.0f, },
	};

	matrix::matrix(int rs, int cs)
	{
		r = rs;
		c = cs;

		data.reserve(r);

		std::vector<float> t_column(cs);
		data = std::vector<std::vector<float>>(rs, t_column);
	}

	matrix::matrix(std::vector<std::vector<float>> d)
	{
		r = d.size();
		c = d[0].size();

		data = d;
	}
}