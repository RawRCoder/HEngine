#pragma once
#include <malloc.h>

typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef signed __int8 s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;
typedef float f32;
typedef double f64;
typedef void* pointer;
typedef union
{
	u32 m_iData;
	u8 m_iChannels[4];

	u8& A() { return m_iChannels[3]; }
	u8& R() { return m_iChannels[2]; }
	u8& G() { return m_iChannels[1]; }
	u8& B() { return m_iChannels[0]; }

	u8 A() const { return m_iChannels[3]; }
	u8 R() const { return m_iChannels[2]; }
	u8 G() const { return m_iChannels[1]; }
	u8 B() const { return m_iChannels[0]; }

	f32 GetAlpha() const { return A() / 255.0f; }
	f32 GetRed() const { return R() / 255.0f; }
	f32 GetGreen() const { return G() / 255.0f; }
	f32 GetBlue() const { return B() / 255.0f; }

	void SetAlpha(f32 v) { A() = static_cast<u8>(v * 255.0f); }
	void SetRed(f32 v) { R() = static_cast<u8>(v * 255.0f); }
	void SetGreen(f32 v) { G() = static_cast<u8>(v * 255.0f); }
	void SetBlue(f32 v) { B() = static_cast<u8>(v * 255.0f); }
} bgra_uint_t;

template<int N>
struct AlignedObject
{
	void* operator new(size_t sz) { return _aligned_malloc(sz, N); }
	void operator delete(void* memory) { _aligned_free(memory); }
};

struct version_s
{
	u32 major, minor, revision, build;
	version_s(u32 _ma, u32 _mi, u32 _re, u32 _bu) : major(_ma), minor(_mi), revision(_re), build(_bu) {}
};