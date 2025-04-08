#pragma once

#include "../pch.hpp"

class MinMax
{
protected:
	const size_t arraySize;

public:
	MinMax(size_t size = 4000) : arraySize(size) {}
	void Do();
};