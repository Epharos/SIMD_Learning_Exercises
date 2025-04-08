#include "../pch.hpp"
//#include "pch.hpp" 
#include "Min_Max.hpp"

void MinMax::Do()
{
	float* a = new float[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = rand();
	}

	Profiler* profiler = new Profiler("Process iterative");
	float min = a[0];
	float max = a[0];
	for (int i = 1; i < arraySize; ++i)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	delete profiler;

	std::cout << "Min: " << min << std::endl;
	std::cout << "Max: " << max << std::endl;

	profiler = new Profiler("Process SIMD 128b");
	size_t realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;

	__m128 minVec = _mm_set1_ps(a[0]);
	__m128 maxVec = _mm_set1_ps(a[0]);

	for (size_t i = 0; i < realArraySize; ++i)
	{
		__m128 vec = _mm_load_ps(&a[i * 4]);
		minVec = _mm_min_ps(minVec, vec);
		maxVec = _mm_max_ps(maxVec, vec);
	}

	float minArray[4];
	float maxArray[4];

	_mm_store_ps(minArray, minVec);
	_mm_store_ps(maxArray, maxVec);
	delete profiler;

	std::cout << "Min: " << minArray[0] << std::endl;
	std::cout << "Max: " << maxArray[0] << std::endl;

	profiler = new Profiler("Process SIMD 256b");
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;

	__m256 minVec256 = _mm256_set1_ps(a[0]);
	__m256 maxVec256 = _mm256_set1_ps(a[0]);

	for (size_t i = 0; i < realArraySize; ++i)
	{
		__m256 vec = _mm256_load_ps(&a[i * 8]);
		minVec256 = _mm256_min_ps(minVec256, vec);
		maxVec256 = _mm256_max_ps(maxVec256, vec);
	}

	float minArray256[8];
	float maxArray256[8];

	_mm256_store_ps(minArray256, minVec256);
	_mm256_store_ps(maxArray256, maxVec256);
	delete profiler;

	std::cout << "Min: " << minArray256[0] << std::endl;
	std::cout << "Max: " << maxArray256[0] << std::endl;

	delete[] a;
}
