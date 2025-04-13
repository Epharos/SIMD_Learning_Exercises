#include "../pch.hpp"
//#include "pch.hpp"
#include "MatrixMultiplication.hpp"

void MatrixMultiplication::ProcessAll()
{
	double scalarTiming = ProcessScalar();
	double sseTiming = ProcessSSE();
	double avxTiming = ProcessAVX();

	std::cout << "SSE is " << 100. - (sseTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
	std::cout << "AVX is " << 100. - (avxTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
}

double MatrixMultiplication::ProcessScalar()
{
	Matrix4x4 A;
	Matrix4x4 B;

	if (!fixedValues)
	{
		for (int i = 0; i < 16; ++i)
		{
			A.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
			B.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
		}
	}
	else
	{
		A.m[0] = 1; A.m[1] = 2; A.m[2] = 3; A.m[3] = 4;
		A.m[4] = 5; A.m[5] = 6; A.m[6] = 7; A.m[7] = 8;
		A.m[8] = 9; A.m[9] = 10; A.m[10] = 11; A.m[11] = 12;
		A.m[12] = 13; A.m[13] = 14; A.m[14] = 15; A.m[15] = 16;

		B.m[0] = -1; B.m[1] = -2; B.m[2] = 3; B.m[3] = 4;
		B.m[4] = 5; B.m[5] = 6; B.m[6] = -7; B.m[7] = 8;
		B.m[8] = 9; B.m[9] = -10; B.m[10] = 11; B.m[11] = -12;
		B.m[12] = -13; B.m[13] = 14; B.m[14] = 15; B.m[15] = -16;
	}

	std::cout << "Matrix A: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << A.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Matrix B: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << B.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	Matrix4x4 C;

	double timing = 0.0;

	Profiler* profiler = new Profiler("Matrix product (Scalar)", &timing);
	for (int count = 0; count < times; count++)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				C.m[i * 4 + j] = 0;
				for (int k = 0; k < 4; ++k)
				{
					C.m[i * 4 + j] += A.m[i * 4 + k] * B.m[k * 4 + j];
				}
			}
		}
	}
	delete profiler;

	std::cout << "Result Scalar: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << C.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	return timing;
}

double MatrixMultiplication::ProcessSSE()
{
	Matrix4x4 A;
	Matrix4x4 B;

	if (!fixedValues)
	{
		for (int i = 0; i < 16; ++i)
		{
			A.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
			B.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
		}
	}
	else
	{
		A.m[0] = 1; A.m[1] = 2; A.m[2] = 3; A.m[3] = 4;
		A.m[4] = 5; A.m[5] = 6; A.m[6] = 7; A.m[7] = 8;
		A.m[8] = 9; A.m[9] = 10; A.m[10] = 11; A.m[11] = 12;
		A.m[12] = 13; A.m[13] = 14; A.m[14] = 15; A.m[15] = 16;

		B.m[0] = -1; B.m[1] = -2; B.m[2] = 3; B.m[3] = 4;
		B.m[4] = 5; B.m[5] = 6; B.m[6] = -7; B.m[7] = 8;
		B.m[8] = 9; B.m[9] = -10; B.m[10] = 11; B.m[11] = -12;
		B.m[12] = -13; B.m[13] = 14; B.m[14] = 15; B.m[15] = -16;
	}

	std::cout << "Matrix A: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << A.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Matrix B: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << B.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	Matrix4x4 C;

	double timing = 0.0;

	B = B.Transpose();

	Profiler* profiler = new Profiler("Matrix product (SSE)", &timing);
	for (int count = 0; count < times; count++)
	{
		__m128 row1 = _mm_load_ps(A.m);
		__m128 row2 = _mm_load_ps(A.m + 4);
		__m128 row3 = _mm_load_ps(A.m + 8);
		__m128 row4 = _mm_load_ps(A.m + 12);

		for (int i = 0; i < 4; ++i)
		{
			__m128 col = _mm_load_ps(&B.m[i * 4]);

			__m128 buff0 = _mm_mul_ps(row1, col);
			__m128 buff1 = _mm_mul_ps(row2, col);
			__m128 buff2 = _mm_mul_ps(row3, col);
			__m128 buff3 = _mm_mul_ps(row4, col);

			buff0 = _mm_hadd_ps(buff0, buff1);
			buff2 = _mm_hadd_ps(buff2, buff3);

			__m128 vecRes = _mm_hadd_ps(buff0, buff2);

			_mm_store_ps(&C.m[i * 4], vecRes);
		}
	}
	delete profiler;

	C = C.Transpose();

	std::cout << "Result SSE: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << C.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	return timing;
}

double MatrixMultiplication::ProcessAVX()
{
	Matrix4x4 A;
	Matrix4x4 B;

	if (!fixedValues)
	{
		for (int i = 0; i < 16; ++i)
		{
			A.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
			B.m[i] = (rand() / (float)RAND_MAX) * 1000 - 500;
		}
	}
	else
	{
		A.m[0] = 1; A.m[1] = 2; A.m[2] = 3; A.m[3] = 4;
		A.m[4] = 5; A.m[5] = 6; A.m[6] = 7; A.m[7] = 8;
		A.m[8] = 9; A.m[9] = 10; A.m[10] = 11; A.m[11] = 12;
		A.m[12] = 13; A.m[13] = 14; A.m[14] = 15; A.m[15] = 16;

		B.m[0] = -1; B.m[1] = -2; B.m[2] = 3; B.m[3] = 4;
		B.m[4] = 5; B.m[5] = 6; B.m[6] = -7; B.m[7] = 8;
		B.m[8] = 9; B.m[9] = -10; B.m[10] = 11; B.m[11] = -12;
		B.m[12] = -13; B.m[13] = 14; B.m[14] = 15; B.m[15] = -16;
	}

	std::cout << "Matrix A: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << A.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Matrix B: " << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << B.m[i * 4 + j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	B = B.Transpose();

	double timing = 0.0;

	float ABatch[8 * 16];
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			ABatch[j * 8 + i] = A.m[j];
		}
	}

	float BBatch[8 * 16];
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			BBatch[j * 8 + i] = B.m[j];
		}
	}

	float CBatch[8 * 16];
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			CBatch[i * 16 + j] = 0;
		}
	}

	Profiler* profiler = new Profiler("Matrix product (AVX)", &timing);
	for (int count = 0; count < times; count += 8)
	{
		for (int row = 0; row < 4; ++row)
		{
			__m256 a0 = _mm256_load_ps(&ABatch[(row * 4) * 8]);
			__m256 a1 = _mm256_load_ps(&ABatch[(row * 4 + 1) * 8]);
			__m256 a2 = _mm256_load_ps(&ABatch[(row * 4 + 2) * 8]);
			__m256 a3 = _mm256_load_ps(&ABatch[(row * 4 + 3) * 8]);

			for (int col = 0; col < 4; ++col)
			{
				__m256 b0 = _mm256_load_ps(&BBatch[(col * 4) * 8]);
				__m256 b1 = _mm256_load_ps(&BBatch[(col * 4 + 1) * 8]);
				__m256 b2 = _mm256_load_ps(&BBatch[(col * 4 + 2) * 8]);
				__m256 b3 = _mm256_load_ps(&BBatch[(col * 4 + 3) * 8]);

				__m256 result = _mm256_add_ps(
					_mm256_add_ps(
						_mm256_mul_ps(a0, b0),
						_mm256_mul_ps(a1, b1)),
					_mm256_add_ps(
						_mm256_mul_ps(a2, b2),
						_mm256_mul_ps(a3, b3)));

				_mm256_store_ps(&CBatch[(row * 4 + col) * 8], result);
			}
		}
	}
	delete profiler;

	std::cout << "Result AVX: " << std::endl;
	for (int i = 0; i < 16; ++i)
	{
		std::cout << CBatch[i * 8] << " ";
		if (i % 4 == 3)
			std::cout << std::endl;
	}

	std::cout << std::endl;

	return timing;
}
