#include "../pch.hpp"
//#include "pch.hpp"
#include "DotProduct.hpp"

void DotProduct::ProcessAll()
{
	double scalarTiming = ProcessScalar();
	double sseTiming = ProcessSSE();
	double avxTiming = ProcessAVX();

	std::cout << "SSE is " << 100. - (sseTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
	std::cout << "AVX is " << 100. - (avxTiming / scalarTiming) * 100. << " % faster than scalar" << std::endl;
}

double DotProduct::ProcessScalar()
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

	double timing = 0.0;
	float result = 0.0f;

	Profiler* profiler = new Profiler("Dot Product (Scalar)", &timing);

	for (int i = 0; i < arraySize; ++i)
	{
		result += a[i].x() * b[i].x() + a[i].y() * b[i].y() + a[i].z() * b[i].z() + a[i].w() * b[i].w();
	}

	delete profiler;
	return timing;
}

double DotProduct::ProcessSSE()
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

	double timing = 0.0;
	float result = 0.0f;

	Profiler* profiler = new Profiler("Dot Product (SSE using horizontal add)", &timing);
	for (int i = 0; i < arraySize; ++i)
	{
		__m128 u = _mm_load_ps(a[i].data);
		__m128 v = _mm_load_ps(b[i].data);

		__m128 mult = _mm_mul_ps(u, v); // [xx' ; yy' ; zz' ; ww']
		__m128 fsum = _mm_hadd_ps(mult, mult); // [xx' + yy' ; zz' + ww' ; xx' + yy' ; zz' + ww']
		fsum = _mm_hadd_ps(fsum, fsum); // [xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww']

		result += _mm_cvtss_f32(fsum);
	}
	delete profiler;

	double manualShuffleTiming = 0.0f;
	result = 0.0f;

	profiler = new Profiler("Dot Product (SSE using manual shuffle)", &manualShuffleTiming);
	for (int i = 0; i < arraySize; i++)
	{
		__m128 u = _mm_load_ps(a[i].data);
		__m128 v = _mm_load_ps(b[i].data);
		__m128 mult = _mm_mul_ps(u, v); // [xx' ; yy' ; zz' ; ww']
		__m128 shuffle = _mm_movehdup_ps(mult); // [yy' ; yy' ; ww' ; ww']
		__m128 add = _mm_add_ps(mult, shuffle); // [xx' + yy' ; yy' + yy' ; zz' + ww' ; ww' + ww']
		shuffle = _mm_movehl_ps(shuffle, add); // [zz' + ww' ; ww' + ww' ; ww' ; ww']
		add = _mm_add_ss(add, shuffle); // [xx' + yy' + zz' + ww' ; ...]
		result += _mm_cvtss_f32(add);
	}
	delete profiler;

	double sse41Timing = 0.0f;
	result = 0.0f;

	profiler = new Profiler("Dot Product (SSE 4.1 using _mm_dp_ps)", &sse41Timing);
	for (int i = 0; i < arraySize; ++i)
	{
		__m128 u = _mm_load_ps(a[i].data);
		__m128 v = _mm_load_ps(b[i].data);
		__m128 mult = _mm_dp_ps(u, v, 0xF1); // [xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww']
		result += _mm_cvtss_f32(mult);
	}

	return std::min<double>({ timing, manualShuffleTiming, sse41Timing });
}

double DotProduct::ProcessAVX()
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

	double timing = 0.0;
	float result = 0.0f;

	Profiler* profiler = new Profiler("Dot Product (AVX)", &timing);
	for (int i = 0; i < arraySize; i += 2)
	{
		__m128 u1 = _mm_load_ps(a[i].data);
		__m128 u2 = _mm_load_ps(a[i + 1].data);
		__m128 v1 = _mm_load_ps(b[i].data);
		__m128 v2 = _mm_load_ps(b[i + 1].data);

		__m256 u = _mm256_set_m128(u2, u1);
		__m256 v = _mm256_set_m128(v2, v1);

		__m256 mult = _mm256_mul_ps(u, v); // x ; y ; z ; w ; a ; b ; c ; d
		__m256 fsum = _mm256_hadd_ps(mult, mult); // x + y ; z + w ; a + b ; c + d ; x + y ; z + w ; a + b ; c + d
		fsum = _mm256_hadd_ps(fsum, fsum); // x + y + z + w ; a + b + c + d ; x + y + z + w ; a + b + c + d ; x + y + z + w ; a + b + c + d ; x + y + z + w ; a + b + c + d
		// We would usually extract the 2 first values of fsum to get the dot products, but we will add them to the result here
		float tmpResult[8];
		_mm256_store_ps(tmpResult, fsum);

		result += tmpResult[0] + tmpResult[1];
	}

	delete profiler;
	return timing;
}
