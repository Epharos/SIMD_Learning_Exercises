#include "../pch.hpp"
//#include "pch.hpp"
#include "BasicArithmetic.hpp"

void BasicArithmetic::ProcessAll()
{
	std::cout << "Basic Arithmetic with floats" << std::endl << "-------" << std::endl;

	double scalar = 0.0f;
	double sse = 0.0f;
	double avx = 0.0f;

#pragma region FLOATS

	float* a = new float[arraySize];
	float* b = new float[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		a[i] = static_cast<float>(i + 1);
		b[i] = static_cast<float>(arraySize - i);
	}

	float* c = new float[arraySize];

#pragma region ADD
	Profiler* profiler = new Profiler("Addition (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = a[i] + b[i];
	}
	delete profiler;

	profiler = new Profiler("Addition (SSE)", &sse);
	size_t realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_add_ps(_mm_load_ps(&a[i * 4]), _mm_load_ps(&b[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Addition (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_add_ps(_mm256_load_ps(&a[i * 8]), _mm256_load_ps(&b[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Subtraction (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = a[i] - b[i];
	}
	delete profiler;

	profiler = new Profiler("Subtraction (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_sub_ps(_mm_load_ps(&a[i * 4]), _mm_load_ps(&b[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Subtraction (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_sub_ps(_mm256_load_ps(&a[i * 8]), _mm256_load_ps(&b[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Multiplication (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = a[i] * b[i];
	}
	delete profiler;

	profiler = new Profiler("Multiplication (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_mul_ps(_mm_load_ps(&a[i * 4]), _mm_load_ps(&b[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Multiplication (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_mul_ps(_mm256_load_ps(&a[i * 8]), _mm256_load_ps(&b[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Division (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = a[i] / b[i];
	}
	delete profiler;

	profiler = new Profiler("Division (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_div_ps(_mm_load_ps(&a[i * 4]), _mm_load_ps(&b[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Division (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_div_ps(_mm256_load_ps(&a[i * 8]), _mm256_load_ps(&b[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Square Root (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = sqrtf(a[i]);
	}
	delete profiler;

	profiler = new Profiler("Square Root (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_sqrt_ps(_mm_load_ps(&a[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Square Root (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_sqrt_ps(_mm256_load_ps(&a[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Reciprocal (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = 1.0f / a[i];
	}
	delete profiler;

	profiler = new Profiler("Reciprocal (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_rcp_ps(_mm_load_ps(&a[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Reciprocal (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_rcp_ps(_mm256_load_ps(&a[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Reciprocal Square Root (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		c[i] = 1.0f / sqrtf(a[i]);
	}
	delete profiler;

	profiler = new Profiler("Reciprocal Square Root (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_ps(&c[i * 4], _mm_rsqrt_ps(_mm_load_ps(&a[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Reciprocal Square Root (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_ps(&c[i * 8], _mm256_rsqrt_ps(_mm256_load_ps(&a[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << std::endl;

	std::cout << "-------" << std::endl;

	delete[] a;
	delete[] b;
	delete[] c;
#pragma endregion

	std::cout << std::endl;
	std::cout << "Basic Arithmetic with integers" << std::endl << "-------" << std::endl;

#pragma region INTEGERS
	int* ai = new int[arraySize];
	int* bi = new int[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		ai[i] = i + 1;
		bi[i] = arraySize - i;
	}

	int* ci = new int[arraySize];

	profiler = new Profiler("Addition (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		ci[i] = ai[i] + bi[i];
	}
	delete profiler;

	profiler = new Profiler("Addition (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_si128((__m128i*)&ci[i * 4], _mm_add_epi32(_mm_load_si128((__m128i*)&ai[i * 4]), _mm_load_si128((__m128i*)&bi[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Addition (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_si256((__m256i*)&ci[i * 8], _mm256_add_epi32(_mm256_load_si256((__m256i*)&ai[i * 8]), _mm256_load_si256((__m256i*)&bi[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Subtraction (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		ci[i] = ai[i] - bi[i];
	}
	delete profiler;

	profiler = new Profiler("Subtraction (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_si128((__m128i*)&ci[i * 4], _mm_sub_epi32(_mm_load_si128((__m128i*)&ai[i * 4]), _mm_load_si128((__m128i*)&bi[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Subtraction (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_si256((__m256i*)&ci[i * 8], _mm256_sub_epi32(_mm256_load_si256((__m256i*)&ai[i * 8]), _mm256_load_si256((__m256i*)&bi[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Multiplication (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		ci[i] = ai[i] * bi[i];
	}
	delete profiler;

	profiler = new Profiler("Multiplication (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_si128((__m128i*)&ci[i * 4], _mm_mullo_epi32(_mm_load_si128((__m128i*)&ai[i * 4]), _mm_load_si128((__m128i*)&bi[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Multiplication (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_si256((__m256i*)&ci[i * 8], _mm256_mullo_epi32(_mm256_load_si256((__m256i*)&ai[i * 8]), _mm256_load_si256((__m256i*)&bi[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;

	std::cout << "---" << std::endl;

	profiler = new Profiler("Division (Scalar)", &scalar);
	for (int i = 0; i < arraySize; ++i)
	{
		ci[i] = ai[i] / bi[i];
	}
	delete profiler;

	profiler = new Profiler("Division (SSE)", &sse);
	realArraySize = arraySize % 4 == 0 ? arraySize / 4 : arraySize / 4 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm_store_si128((__m128i*)&ci[i * 4], _mm_div_epi32(_mm_load_si128((__m128i*)&ai[i * 4]), _mm_load_si128((__m128i*)&bi[i * 4])));
	}
	delete profiler;

	profiler = new Profiler("Division (AVX)", &avx);
	realArraySize = arraySize % 8 == 0 ? arraySize / 8 : arraySize / 8 + 1;
	for (size_t i = 0; i < realArraySize; ++i)
	{
		_mm256_store_si256((__m256i*)&ci[i * 8], _mm256_div_epi32(_mm256_load_si256((__m256i*)&ai[i * 8]), _mm256_load_si256((__m256i*)&bi[i * 8])));
	}
	delete profiler;

	std::cout << std::endl;

	std::cout << "SSE is " << 100.f - (sse / scalar) * 100 << "% faster than Scalar" << std::endl;
	std::cout << "AVX is " << 100.f - (avx / scalar) * 100 << "% faster than Scalar" << std::endl;
#pragma endregion
}

double BasicArithmetic::ProcessScalar()
{
	throw std::runtime_error("Use ProcessAll instead");
	return -1.0;
}

double BasicArithmetic::ProcessSSE()
{
	throw std::runtime_error("Use ProcessAll instead");
	return -1.0;
}

double BasicArithmetic::ProcessAVX()
{
	throw std::runtime_error("Use ProcessAll instead");
	return -1.0;
}
