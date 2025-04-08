#include "../pch.hpp"
//#include "pch.hpp"
#include "DotProduct.hpp"

void DotProduct::Do()
{
	Vector4f* a = new Vector4f[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		a[i].data[0] = static_cast<float>(i + 1);
		a[i].data[1] = static_cast<float>(arraySize - i);
		a[i].data[2] = static_cast<float>(i + 1);
		a[i].data[3] = static_cast<float>(arraySize - i);
	}

	Vector4f* b = new Vector4f[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		b[i].data[0] = static_cast<float>(i + 1);
		b[i].data[1] = static_cast<float>(arraySize - i);
		b[i].data[2] = static_cast<float>(i + 1);
		b[i].data[3] = static_cast<float>(arraySize - i);
	}

	Profiler* profiler = new Profiler("Dot Product (iterative)");
	float result = 0.0f;
	for (int i = 0; i < arraySize; ++i)
	{
		result += a[i].DotIterative(b[i]);
	}
	delete profiler;

	profiler = new Profiler("Dot Product (SIMD 128b) [using _mm_hadd_ps]");
	float resultSIMD128 = 0.0f;
	for (int i = 0; i < arraySize; ++i)
	{
		resultSIMD128 += a[i].DotSIMD128(b[i]);
	}
	delete profiler;

	profiler = new Profiler("Dot Product (SIMD 128b) [using manual shuffle]");
	float resultSIMD128_Sol = 0.0f;
	for (int i = 0; i < arraySize; ++i)
	{
		resultSIMD128_Sol += a[i].DotSIMD128_Sol(b[i]);
	}
	delete profiler;

	profiler = new Profiler("Dot Product (SIMD 128b) [using _mm_dp_ps]");
	float resultSIMD128_SSE41 = 0.0f;
	for (int i = 0; i < arraySize; ++i)
	{
		resultSIMD128_SSE41 += a[i].DotSIMD128_SSE41(b[i]);
	}
	delete profiler;

	delete[] a;
	delete[] b;

	//std::cout << "Sanity check: " << ((result == resultSIMD128 == resultSIMD128_Sol == resultSIMD128_SSE41) ? "YES" : "NO") << std::endl;
	std::cout << "Result: " << result << std::endl;
	std::cout << "Result SIMD 128: " << resultSIMD128 << std::endl;
	std::cout << "Result SIMD 128 Sol: " << resultSIMD128_Sol << std::endl;
	std::cout << "Result SIMD 128 SSE41: " << resultSIMD128_SSE41 << std::endl;
}
