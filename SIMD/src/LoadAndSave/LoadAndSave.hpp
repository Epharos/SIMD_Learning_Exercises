#pragma once

#include "../pch.hpp"

class LoadAndSave
{
protected:
	const size_t arraySize;

public:
	LoadAndSave(size_t _arraySize = 4) : arraySize(_arraySize) {}

	void Do();
};