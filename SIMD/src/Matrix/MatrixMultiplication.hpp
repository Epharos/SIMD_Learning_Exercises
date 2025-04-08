#pragma once

#include "../pch.hpp"

struct Matrix4x4
{
	float m[16];

	Matrix4x4 MultiplySIMD128(const Matrix4x4& other)
	{
		Matrix4x4 result;
		
		__m128 row1 = _mm_load_ps(m);
		__m128 row2 = _mm_load_ps(m + 4);
		__m128 row3 = _mm_load_ps(m + 8);
		__m128 row4 = _mm_load_ps(m + 12);

		for (int i = 0; i < 4; ++i)
		{
			__m128 col = _mm_load_ps(&other.m[i * 4]);

			__m128 buff0 = _mm_mul_ps(row1, col);
			__m128 buff1 = _mm_mul_ps(row2, col);
			__m128 buff2 = _mm_mul_ps(row3, col);
			__m128 buff3 = _mm_mul_ps(row4, col);

			buff0 = _mm_hadd_ps(buff0, buff1);
			buff2 = _mm_hadd_ps(buff2, buff3);

			__m128 vecRes = _mm_hadd_ps(buff0, buff2);

			_mm_store_ps(&result.m[i * 4], vecRes);
		}

		return result;
	}

	Matrix4x4 Transpose()
	{
		Matrix4x4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i * 4 + j] = m[j * 4 + i];
			}
		}

		return result;
	}

	void Print()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::cout << m[i * 4 + j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class MatrixMultiplication
{
protected:
	int times;
	bool fixedValues;

public:
	MatrixMultiplication(int times = 1, bool fixedValues = false) : times(times), fixedValues(fixedValues) {}
	void Do();
};