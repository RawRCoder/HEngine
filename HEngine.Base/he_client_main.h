/****************************************************
*	Header to include to any of custom client DLL	*
*	All functions are to be implemented on client	*
*****************************************************/
#pragma once
#include "hengine.h"

#ifndef __HE_CLIENT_DLL
API extern DGetHEngineVersion	cli_GetHEngineVersion;
API extern DGetDllVersion		cli_GetVersion;
API extern DGetDllName			cli_GetName;
#else
#include <string>
#define GAME_API __declspec(dllexport)
/// === client.dll -> HEngine ===========
GAME_API u32			cli_GetHEngineVersion(void);
GAME_API version_s		cli_GetVersion();
GAME_API std::string	cli_GetName();
#endif