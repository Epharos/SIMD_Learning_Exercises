#pragma once

#include "../pch.hpp"

class BasicArithmetic
{
protected:
	const size_t arraySize;
public:
	BasicArithmetic(size_t _arraySize = 4) : arraySize(_arraySize) {}
	void Do();
};