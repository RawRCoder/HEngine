#pragma once
#include "common.h"
#include <time.h>

class PerfomanceCounter
{
public:
	void Start();
	f64 GetTime();
	void Tick(u64 amount = 1);
	f64 GetTicksPerSecond();
private:
	clock_t m_start;
	u64 m_iCounter;
};
