#include "he_main.h"
#include "globals.h"

u32	cli_GetHEngineVersion()
{ return HENGINE_VERSION; }

version_s cli_GetVersion()
{ return HEDEMO_VERSION; }

std::string	cli_GetName()
{ return "HEngine Demo"; }