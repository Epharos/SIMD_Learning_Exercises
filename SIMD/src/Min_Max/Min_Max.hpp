#pragma once

#include "../pch.hpp"
#include "../Exercise.hpp"

class MinMax : public Exercise
{
protected:
	const size_t arraySize;

public:
	MinMax(size_t size = 4000) : arraySize(size) {}
	void ProcessAll();
	double ProcessScalar();
	double ProcessSSE();
	double ProcessAVX();
};