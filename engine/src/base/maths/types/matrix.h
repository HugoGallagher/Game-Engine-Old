#pragma once
#include "pch.h"
#include "macros.h"

namespace engine
{
	class DLL matrix
	{
	public:
		int r, c;
		std::vector<std::vector<float>> data;

		static std::vector<std::vector<float>> imatrix;

		matrix() {}
		matrix(int rs, int cs);
		matrix(std::vector<std::vector<float>>);

		static bool same_size(matrix& m1, matrix& m2) { return m1.r == m2.r && m1.c == m2.c; }

		matrix operator+(matrix& m)
		{
			if (this->r == m.r && this->c == m.c)
			{
				std::vector<std::vector<float>> d(this->r, std::vector<float>(this->c));

				for (int i = 0; i < this->r; i++) { for (int j = 0; j < this->c; j++)
				{
					d[i][j] = this->data[i][j] + m.data[i][j];
				}}

				return matrix(d);
			}
		}
		matrix operator-(matrix& m)
		{
			if (this->r == m.r && this->c == m.c)
			{
				std::vector<std::vector<float>> d(this->r, std::vector<float>(this->c));

				for (int i = 0; i < this->r; i++) { for (int j = 0; j < this->c; j++)
				{
					d[i][j] = this->data[i][j] - m.data[i][j];
				}}

				return matrix(d);
			}
		}

		matrix operator*(matrix& m)
		{
			if (this->r == m.c)
			{
				std::vector<std::vector<float>> d(this->r, std::vector<float>(this->c));

				for (int i = 0; i < this->r; i++) { for (int j = 0; j < this->c; j++)
				{
					float t = 0;

					for (int k = 0; k < this->c; k++)
					{
						t += this->data[i][k] * m.data[k][j];
					}

					d[i][j] = t;
				}}

				return matrix(d);
			}
		}
	};
}