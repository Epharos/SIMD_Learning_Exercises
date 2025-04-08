#pragma once

#include "../pch.hpp"

struct Vector4f
{
	alignas(16) float data[4];

	float x() const { return data[0]; }
	float y() const { return data[1]; }
	float z() const { return data[2]; }
	float w() const { return data[3]; }

	float DotIterative(const Vector4f& other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z() + w() * other.w();
	}

	float DotSIMD128(const Vector4f& other) const
	{
		__m128 u = _mm_load_ps(data);
		__m128 v = _mm_load_ps(other.data);
		__m128 mult = _mm_mul_ps(u, v); // [xx' ; yy' ; zz' ; ww']
		__m128 fsum = _mm_hadd_ps(mult, mult); // [xx' + yy' ; zz' + ww' ; xx' + yy' ; zz' + ww']
		fsum = _mm_hadd_ps(fsum, fsum); // [xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww']
		return _mm_cvtss_f32(fsum); // xx' + yy' + zz' + ww'
	}

	float DotSIMD128_Sol(const Vector4f other) const
	{
		__m128 u = _mm_load_ps(data);
		__m128 v = _mm_load_ps(other.data);
		__m128 mult = _mm_mul_ps(u, v); // [xx' ; yy' ; zz' ; ww']
		
		__m128 shuffle = _mm_movehdup_ps(mult); // [yy' ; yy' ; ww' ; ww']
		__m128 add = _mm_add_ps(mult, shuffle); // [xx' + yy' ; yy' + yy' ; zz' + ww' ; ww' + ww']
		shuffle = _mm_movehl_ps(shuffle, add); // [zz' + ww' ; ww' + ww' ; ww' ; ww']
		add = _mm_add_ss(add, shuffle); // [xx' + yy' + zz' + ww' ; ...]
		return _mm_cvtss_f32(add); // xx' + yy' + zz' + ww'
	}

	float DotSIMD128_SSE41(const Vector4f& other) const
	{
		__m128 u = _mm_load_ps(data);
		__m128 v = _mm_load_ps(other.data);
		__m128 mult = _mm_dp_ps(u, v, 0xF1); // [xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww' ; xx' + yy' + zz' + ww']
		return _mm_cvtss_f32(mult); // xx' + yy' + zz' + ww'
	}
};

class DotProduct
{
protected:
	const size_t arraySize;
public:
	DotProduct(size_t _arraySize = 4) : arraySize(_arraySize) {}
	void Do();
};