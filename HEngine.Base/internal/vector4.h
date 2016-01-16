#pragma once

#pragma once
#include <math.h>
#include "common.h"
#include "vectorfuncs.h"

struct alignas(16) float4
{
	f32 x, y, z, w;

	float4() {};
	explicit float4(f32 _x) : x(_x), y(_x), z(_x), w(_x) {};
	float4(f32 _x, f32 _y) : x(_x), y(_y) {};
	float4(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {};
	float4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) {};

	f32& operator[](u32 i) { return asPtr()[i]; }
	f32* asPtr() { return reinterpret_cast<f32*>(this); }
	const f32* asCPtr() const { return reinterpret_cast<const f32*>(this); }

	f32 lengthSq() const { return x*x + y*y + z*z + w*w; }
	f32 length() const { return sqrtf(lengthSq()); }

	void add(const float4& b)
	{
		sse_sum(this, &b);
	}
	void sub(const float4& b)
	{
		sse_sub(this, &b);
	}
	void mul(const float4& b)
	{
		sse_mul(this, &b);
	}
	void mul(const f32& b)
	{
		float4 B{ b };
		sse_mul(this, &B);
	}
	void div(const float4& b)
	{
		sse_div(this, &b);
	}
	void div(const f32& b)
	{
		float4 B{ b };
		sse_mul(this, &B);
	}
	void negate()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}
	void normalize()
	{
		div(length());
	}
	float4 normalized() const
	{
		float4 t{ x, y, z, w };
		t.div(length());
		return t;
	}
	float4 negated() const { return float4(-x, -y, -z, -w); }
	bool isCloseToZero(f32 delta) const
	{
		return (fabsf(x) <= delta) && (fabsf(y) <= delta) && (fabsf(z) <= delta) && (fabsf(w) <= delta);
	}
	bool isCloseTo(const float4& other, f32 delta) const
	{
		auto c = other;
		c.sub(*this);
		return c.isCloseToZero(delta);
	}
};

static float4* vector4FromPtr(f32* ptr)
{
	return reinterpret_cast<float4*>(ptr);
}
static float4 operator+(const float4& A, const float4& B)
{
	auto C = A;
	C.add(B);
	return C;
}
static float4 operator-(const float4& A, const float4& B)
{
	auto C = A;
	C.sub(B);
	return C;
}
static float4 operator*(const float4& A, f32 B)
{
	auto C = A;
	C.mul(B);
	return C;
}
static float4 operator*(f32 B, const float4& A)
{
	auto C = A;
	C.mul(B);
	return C;
}
static float4 operator/(const float4& A, f32 B)
{
	auto C = A;
	C.div(B);
	return C;
}
static float4 operator/(f32 B, const float4& A)
{
	auto C = A;
	C.div(B);
	return C;
}
static float4 operator!(const float4& A)
{
	return A.normalized();
}
static float4 operator-(const float4& A)
{
	return A.negated();
}

static f32 dot(const float4& a, const float4& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}
static f32 dot3(const float4& a, const float4& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
static float4 cross3(const float4& a, const float4& b)
{
	return{ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}
static float4 cross3l(const float4& a, const float4& b)
{
	return{ a.z*b.y - a.y*b.z, a.x*b.z - a.z*b.x, a.y*b.x - a.x*b.y };
}
static f32 angleCosBetween(const float4& a, const float4& b)
{
	return dot(a, b) / sqrtf(a.lengthSq()*b.lengthSq());
}
static f32 angleCosBetween3(const float4& a, const float4& b)
{
	return dot3(a, b) / sqrtf((a.x*a.x + a.y*a.y + a.z*a.z)*(b.x*b.x + b.y*b.y + b.z*b.z));
}
static f32 angleBetween(const float4& a, const float4& b)
{
	return acosf(angleCosBetween(a, b));
}
static f32 angleBetween3(const float4& a, const float4& b)
{
	return acosf(angleCosBetween3(a, b));
}