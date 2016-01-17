#include "dll_loader.h"
#include "he_server_main.h"
#include "he_client_main.h"
#include <iostream>

DllLoader g_DllLoader;
DGetHEngineVersion	cli_GetHEngineVersion = nullptr;
DGetDllVersion		cli_GetVersion = nullptr;
DGetDllName			cli_GetName = nullptr;

DGetHEngineVersion	srv_GetHEngineVersion = nullptr;
DGetDllVersion		srv_GetVersion = nullptr;
DGetDllName			srv_GetName = nullptr;

DllLoader::DllLoader()
{
}


DllLoader::~DllLoader()
{
}

HMODULE DllLoader::LoadClientDLL(const std::wstring& fileName)
{
	HMODULE hDll = LoadLibraryW(fileName.c_str());
	if (!hDll) {
		//TODO: Log
		std::cout << "Failed to load DLL '" << fileName.c_str() << "'" << std::endl;
		return nullptr;
	}
	auto fGetVersion = reinterpret_cast<DGetHEngineVersion>(GetProcAddress(hDll, (LPCSTR)1));
	if (!fGetVersion) {
		std::cout << "Failed to locate cli_GetHEngineVersion() in '" << fileName.c_str() << "'" << std::endl;
		FreeLibrary(hDll);
		return nullptr;
	}

	auto v = fGetVersion();
	if (v != HENGINE_VERSION) {
		std::cout << "cli_GetHEngineVersion() = " << v << ", expexted " << HENGINE_VERSION << " in '" << fileName.c_str() << "'" << std::endl;
		FreeLibrary(hDll);
		return nullptr;
	}

	m_hClientDll = hDll;

	cli_GetHEngineVersion = fGetVersion;
	cli_GetVersion = reinterpret_cast<DGetDllVersion>(GetProcAddress(m_hClientDll, (LPCSTR)3));
	cli_GetName = reinterpret_cast<DGetDllName>(GetProcAddress(m_hClientDll, (LPCSTR)2));

	return hDll;
}

HMODULE DllLoader::LoadServerDLL(const std::wstring& fileName)
{
	HMODULE hDll = LoadLibraryW(fileName.c_str());
	if (!hDll) {
		//TODO: Log
		std::cout << "Failed to load DLL '" << fileName.c_str() << "'" << std::endl;
		return nullptr;
	}
	auto fGetVersion = reinterpret_cast<DGetHEngineVersion>(GetProcAddress(hDll, (LPCSTR)1));
	if (!fGetVersion) {
		std::cout << "Failed to locate srv_GetHEngineVersion() in '" << fileName.c_str() << "'" << std::endl;
		FreeLibrary(hDll);
		return nullptr;
	}

	auto v = fGetVersion();
	if (v != HENGINE_VERSION) {
		std::cout << "srv_GetHEngineVersion() = " << v << ", expexted " << HENGINE_VERSION << " in '" << fileName.c_str() << "'" << std::endl;
		FreeLibrary(hDll);
		return nullptr;
	}

	m_hServerDll = hDll;
	srv_GetHEngineVersion = fGetVersion;
	srv_GetVersion = reinterpret_cast<DGetDllVersion>(GetProcAddress(m_hServerDll, (LPCSTR)3));
	srv_GetName = reinterpret_cast<DGetDllName>(GetProcAddress(m_hServerDll, (LPCSTR)2));
	return hDll;
}
