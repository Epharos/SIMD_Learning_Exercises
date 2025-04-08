#pragma once

#include "../pch.hpp"

class MatrixMultiplyVector
{
protected:
	const size_t times;
	bool fixedValues;
public:
	MatrixMultiplyVector(size_t _times = 1, bool _fixedValues = false) : times(_times), fixedValues(_fixedValues) {}
	void Do();
};