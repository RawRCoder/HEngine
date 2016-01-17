/****************************************************
*	Header to include to any of custom server DLL	*
*	All functions are to be implemented on server	*
*****************************************************/
#pragma once
#include "hengine.h"
#ifndef __HE_SERVER_DLL
API extern DGetHEngineVersion	srv_GetHEngineVersion;
API extern DGetDllVersion		srv_GetVersion;
API extern DGetDllName			srv_GetName;
#else
#include <string>
#define GAME_API __declspec(dllexport)
/// === server.dll -> HEngine ===========
GAME_API u32			srv_GetHEngineVersion(void);
GAME_API version_s		srv_GetVersion();
GAME_API std::string	srv_GetName();
#endif