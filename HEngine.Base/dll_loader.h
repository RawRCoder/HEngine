#pragma once
#include "internal/array.h"
#include "hengine.h"
#include <windows.h>

class DllLoader
{
public:
	DllLoader();
	~DllLoader();

	API HMODULE LoadClientDLL(const std::wstring& fileName);
	API HMODULE LoadServerDLL(const std::wstring& fileName);
private:
	HMODULE m_hClientDll = nullptr;
	HMODULE m_hServerDll = nullptr;
};

API extern DllLoader g_DllLoader;