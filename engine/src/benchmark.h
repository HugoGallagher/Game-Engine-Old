#pragma once

#include "pch.h"

#include "base/logger.h"
#include "base/input.h"

#include "base/maths/types/vector4.h"
#include "base/maths/types/matrix4.h"
#include "mat4x4.hpp"
#include "matrix.hpp"

#include <gtc/matrix_transform.hpp>

namespace engine
{
	class benchmark
	{
	public:
		int repeat = 1000;

		benchmark() {}

		clock_t start_time, end_time;

		float x1 = 538;
		float y1 = 729;

		float x2 = 420;
		float y2 = 690;

		void run_benchmark()
		{
			std::cin.get();
			std::cout << "Benchmark started" << std::endl;

			const int r = 5;
			clock_t avg1, avg2;
			clock_t time1 = 0;
			clock_t time2 = 0;
			clock_t time_taken;

			for (int j = 0; j < r; j++)
			{
				start_time = clock();
				benchmark_function1();
				end_time = clock();
				time_taken = end_time - start_time;
				time1 += time_taken;
				std::cout << "Function 1: " << time_taken << std::endl;

				start_time = clock();
				benchmark_function2();
				end_time = clock();
				time_taken = end_time - start_time;
				time2 += time_taken;
				std::cout << "Function 2: " << time_taken << std::endl << std::endl;
			}

			std::cout << "Function 1 average: " << time1 / r << std::endl;
			std::cout << "Function 2 average: " << time2 / r << std::endl;
		}

		void benchmark_function1()
		{
			std::vector<std::vector<float>> d1 =
			{
				{ 2.0f, 0.0f, 0.0f, 1.0f, },
				{ 0.0f, 2.0f, 0.0f, 2.0f, },
				{ 0.0f, 0.0f, 2.0f, 3.0f, },
				{ 0.0f, 0.0f, 0.0f, 1.0f, }
			};
			std::vector<std::vector<float>> d2 =
			{
				{ 2.0f, 4.0f, 6.0f, 3.0f, },
				{ 8.0f, 6.0f, 7.0f, 3.0f, },
				{ 9.0f, 2.0f, 7.0f, 5.0f, },
				{ 9.0f, 5.0f, 8.0f, 3.0f, }
			};

			matrix4 m1 = matrix4(d1);
			matrix4 m2 = matrix4(d2);

			matrix4 m3;
			vector4 v(6.0f, 2.0f, 8.0f, 1.0f);

			for (int i = 0; i < repeat; i++)
			{
				m3.transform(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f);
			}
			
			/*for (int i = 0; i < 4; i++)
			{
				float v[4];
				_mm_store_ps(v, m3.data[i]);
				for (int j = 0; j < 4; j++)
				{
					std::cout << v[j] << ", ";
				}
				std::cout << std::endl;
			}*/
		}

		void benchmark_function2()
		{
			glm::mat4 m1(1.0f);
			m1[0][3] = 1.0f;
			m1[1][3] = 2.0f;
			m1[2][3] = 3.0f;
			
			glm::mat4 m2(1.0f);
			m2[0][0] = 2.0f;
			m2[1][1] = 2.0f;
			m2[2][2] = 2.0f;

			glm::mat4 m3;
			glm::vec4 v;

			for (int i = 0; i < repeat; i++)
			{
				v = m1 * v;
			}
		}
	};
}