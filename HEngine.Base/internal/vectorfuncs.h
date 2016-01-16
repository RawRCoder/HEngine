#pragma once

static void sse_sum(const void* A, const void* B, void* C)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;
		lea edx, C;

		mov eax, [eax];
		mov ebx, [ebx];
		mov edx, [edx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		addps xmm0, xmm1;
		movaps[edx], xmm0;
	}
}
static void sse_sub(const void* A, const void* B, void* C)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;
		lea edx, C;

		mov eax, [eax];
		mov ebx, [ebx];
		mov edx, [edx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		subps xmm0, xmm1;
		movaps[edx], xmm0;
	}
}
static void sse_mul(const void* A, const void* B, void* C)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;
		lea edx, C;

		mov eax, [eax];
		mov ebx, [ebx];
		mov edx, [edx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		mulps xmm0, xmm1;
		movaps[edx], xmm0;
	}
}
static void sse_div(const void* A, const void* B, void* C)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;
		lea edx, C;

		mov eax, [eax];
		mov ebx, [ebx];
		mov edx, [edx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		divps xmm0, xmm1;
		movaps[edx], xmm0;
	}
}

static void sse_sum(void* A, const void* B)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;

		mov eax, [eax];
		mov ebx, [ebx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		addps xmm0, xmm1;
		movaps[eax], xmm0;
	}
}
static void sse_sub(const void* A, const void* B)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;

		mov eax, [eax];
		mov ebx, [ebx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		subps xmm0, xmm1;
		movaps[eax], xmm0;
	}
}
static void sse_mul(const void* A, const void* B)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;

		mov eax, [eax];
		mov ebx, [ebx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		mulps xmm0, xmm1;
		movaps[eax], xmm0;
	}
}
static void sse_div(const void* A, const void* B)
{
	__asm
	{
		lea eax, A;
		lea ebx, B;

		mov eax, [eax];
		mov ebx, [ebx];

		movaps xmm0, [eax];
		movaps xmm1, [ebx];
		divps xmm0, xmm1;
		movaps[eax], xmm0;
	}
}
