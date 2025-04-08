#include "../pch.hpp"
//#include "pch.hpp"
#include "MatrixMultiplyVector.hpp"

void MatrixMultiplyVector::Do()
{
	float* mat = new float[16]; // 4x4 matrix
	float* vec = new float[4]; // 4x1 matrix
	float* res = new float[4]; // 4x1 matrix

	if (!fixedValues)
	{
		for (int i = 0; i < 16; ++i)
		{
			mat[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
		}

		for (int i = 0; i < 4; ++i)
		{
			vec[i] = (rand() / (float)RAND_MAX) * 400 - 200;
		}
	}
	else
	{
		mat[0] = 1; mat[1] = 2; mat[2] = 3; mat[3] = 4;
		mat[4] = 5; mat[5] = 6; mat[6] = 7; mat[7] = 8;
		mat[8] = 9; mat[9] = 10; mat[10] = 11; mat[11] = 12;
		mat[12] = 13; mat[13] = 14; mat[14] = 15; mat[15] = 16;

		vec[0] = 1;
		vec[1] = 2;
		vec[2] = 3;
		vec[3] = 4;
	}

	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << mat[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Vector: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl << std::endl;

	Profiler* profiler = new Profiler("Process iterative");
	for (int count = 0; count < times; ++count)
	{
		for (int i = 0; i < 4; ++i)
		{
			res[i] = 0;
			for (int j = 0; j < 4; ++j)
			{
				res[i] += mat[i * 4 + j] * vec[j];
			}
		}
	}
	delete profiler;

	std::cout << "Result: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << res[i] << " ";
	}
	std::cout << std::endl << std::endl;

	profiler = new Profiler("Process SIMD 128b");
	for (int count = 0; count < times; ++count)
	{
		__m128 vecRes = _mm_setzero_ps(); // result vector

		__m128 mat0 = _mm_load_ps(mat); // first row of the matrix
		__m128 mat1 = _mm_load_ps(mat + 4); // second row of the matrix
		__m128 mat2 = _mm_load_ps(mat + 8); // third row of the matrix
		__m128 mat3 = _mm_load_ps(mat + 12); // fourth row of the matrix

		__m128 vec0 = _mm_load_ps(vec); // vector

		__m128 buff0 = _mm_mul_ps(mat0, vec0); //first row (mat0x * vec0x ; mat0y * vec0y ; mat0z * vec0z ; mat0w * vec0w)
		__m128 buff1 = _mm_mul_ps(mat1, vec0); //second row (mat1x * vec0x ; mat1y * vec0y ; mat1z * vec0z ; mat1w * vec0w)
		__m128 buff2 = _mm_mul_ps(mat2, vec0); //third row (mat2x * vec0x ; mat2y * vec0y ; mat2z * vec0z ; mat2w * vec0w)
		__m128 buff3 = _mm_mul_ps(mat3, vec0); //fourth row (mat3x * vec0x ; mat3y * vec0y ; mat3z * vec0z ; mat3w * vec0w)

		buff0 = _mm_hadd_ps(buff0, buff1);
		buff2 = _mm_hadd_ps(buff2, buff3);

		vecRes = _mm_hadd_ps(buff0, buff2);

		_mm_store_ps(res, vecRes); // store result
	}
	delete profiler;

	std::cout << "Result SIMD: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << res[i] << " ";
	}
	std::cout << std::endl << std::endl;

	profiler = new Profiler("Process SIMD 128b Provided Solution");
	for (int count = 0; count < times; count++)
	{
		__m128 v = _mm_load_ps(vec);

		for (int i = 0; i < 4; ++i) {
			__m128 row = _mm_load_ps(mat + i * 4);
			__m128 mul = _mm_mul_ps(row, v);
			__m128 shuf1 = _mm_movehl_ps(mul, mul);
			__m128 sum1 = _mm_add_ps(mul, shuf1);
			__m128 shuf2 = _mm_shuffle_ps(sum1, sum1, 1);
			__m128 dot = _mm_add_ss(sum1, shuf2);

			_mm_store_ss(res + i, dot);
		}
	}
	delete profiler;

	std::cout << "Result SIMD Provided Solution: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << res[i] << " ";
	}
	std::cout << std::endl << std::endl;

	profiler = new Profiler("Process SIMD 256b");
	float res256[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // result vector

	for (int count = 0; count < times; count++)
	{
		__m256 mat0 = _mm256_load_ps(mat); // first and second rows of the matrix
		__m256 mat1 = _mm256_load_ps(mat + 8); // third and fourth rows of the matrix
		__m128 v = _mm_load_ps(vec);
		__m256 vec0 = _mm256_set_m128(v, v); // vector (duplicated to be used in 256_mul)

		__m256 buff0 = _mm256_dp_ps(mat0, vec0, 0xF1);
		__m256 buff1 = _mm256_dp_ps(mat1, vec0, 0xF2);

		__m256 re = _mm256_or_ps(buff0, buff1);
		_mm256_store_ps(res256, re);
	}

	res[0] = res256[0];
	res[1] = res256[4];
	res[2] = res256[1];
	res[3] = res256[5];

	delete profiler;

	std::cout << "Result SIMD 256b: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << res[i] << " ";
	}
	std::cout << std::endl << std::endl;
}
