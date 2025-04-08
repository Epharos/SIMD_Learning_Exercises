#include "../pch.hpp"
//#include "pch.hpp"
#include "LoadAndSave.hpp"

#include <array>

void LoadAndSave::Do()
{
	float* a = new float[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	Profiler* profiler = new Profiler("Process iterative");
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = a[i] * 2.0f;
	}
	delete profiler;

	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	profiler = new Profiler("Process SIMD 128b");
	size_t realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&a[i * 4], _mm_mul_ps(_mm_load_ps(&a[i * 4]), _mm_set1_ps(2.0f)));
	}
	delete profiler;

	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	profiler = new Profiler("Process SIMD 256b");
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&a[i * 8], _mm256_mul_ps(_mm256_load_ps(&a[i * 8]), _mm256_set1_ps(2.0f)));
	}
	delete profiler;

	delete[] a;
}
