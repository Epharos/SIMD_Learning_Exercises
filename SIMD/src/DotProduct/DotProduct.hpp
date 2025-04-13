#pragma once

#include "../pch.hpp"
#include "../Exercise.hpp"

struct Vector4f
{
	alignas(16) float data[4];

	float x() const { return data[0]; }
	float y() const { return data[1]; }
	float z() const { return data[2]; }
	float w() const { return data[3]; }
};

class DotProduct : public Exercise
{
protected:
	const size_t arraySize;
public:
	DotProduct(size_t _arraySize = 4) : arraySize(_arraySize) {}
	void ProcessAll();
	double ProcessScalar();
	double ProcessSSE();
	double ProcessAVX();
};