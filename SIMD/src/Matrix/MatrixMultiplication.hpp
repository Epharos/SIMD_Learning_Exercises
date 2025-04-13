#pragma once

#include "../pch.hpp"
#include "../Exercise.hpp"

struct Matrix4x4
{
	float m[16];

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

class MatrixMultiplication : public Exercise
{
protected:
	int times;
	bool fixedValues;

public:
	MatrixMultiplication(int times = 1, bool fixedValues = false) : times(times), fixedValues(fixedValues) {}
	void ProcessAll();
	double ProcessScalar();
	double ProcessSSE();
	double ProcessAVX();
};