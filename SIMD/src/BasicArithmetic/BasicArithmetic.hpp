#pragma once

#include "../pch.hpp"
#include "../Exercise.hpp"

class BasicArithmetic : public Exercise
{
protected:
	const size_t arraySize;
public:
	BasicArithmetic(size_t _arraySize = 4) : arraySize(_arraySize) {}
	void ProcessAll();
	double ProcessScalar();
	double ProcessSSE();
	double ProcessAVX();
};