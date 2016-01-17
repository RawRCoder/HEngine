#include "he_main.h"
#include "../HEDemo.Client/globals.h"

u32	srv_GetHEngineVersion()
{return HENGINE_VERSION;}

version_s srv_GetVersion()
{return HEDEMO_VERSION;}

std::string	srv_GetName()
{return "HEngine Demo";}