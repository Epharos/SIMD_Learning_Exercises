#include "../pch.hpp"
//#include "pch.hpp"
#include "LoadAndSave.hpp"

void LoadAndSave::ProcessAll()
{
	double scalarTiming = ProcessScalar();
	double sseTiming = ProcessSSE();
	double avxTiming = ProcessAVX();

	std::cout << "SSE is " << 100. - (sseTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
	std::cout << "AVX is " << 100. - (avxTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
}

double LoadAndSave::ProcessScalar()
{
	double timing = 0.0;

	float* a = new float[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	Profiler* profiler = new Profiler("Load and Save (Scalar)", &timing);
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = a[i] * 2.0f;
	}
	delete profiler;
	delete[] a;

	return timing;
}

double LoadAndSave::ProcessSSE()
{
	double timing = 0.0;

	float* a = new float[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	Profiler* profiler = new Profiler("Load And Save (SSE)", &timing);
	size_t realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&a[i * 4], _mm_mul_ps(_mm_load_ps(&a[i * 4]), _mm_set1_ps(2.0f)));
	}
	delete profiler;
	delete[] a;

	return timing;
}

double LoadAndSave::ProcessAVX()
{
	double timing = 0.0;

	float* a = new float[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
	}

	Profiler* profiler = new Profiler("Load And Save (AVX)", &timing);
	size_t realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&a[i * 8], _mm256_mul_ps(_mm256_load_ps(&a[i * 8]), _mm256_set1_ps(2.0f)));
	}
	delete profiler;
	delete[] a;

	return timing;
}
