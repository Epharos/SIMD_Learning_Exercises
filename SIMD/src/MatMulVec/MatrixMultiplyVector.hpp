#pragma once

#include "../pch.hpp"
#include "../Exercise.hpp"

class MatrixMultiplyVector : public Exercise
{
protected:
	const size_t times;
	bool fixedValues;
public:
	MatrixMultiplyVector(size_t _times = 1, bool _fixedValues = false) : times(_times), fixedValues(_fixedValues) {}
	void ProcessAll();
	double ProcessScalar();
	double ProcessSSE();
	double ProcessAVX();
};