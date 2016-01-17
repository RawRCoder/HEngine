#include "api_shaders.h"
#include <ioutils.h>

GLuint LoadShaderFromFile(const std::wstring& fileName, GLenum type)
{
	auto ss = ReadToEndAsString(fileName);
	auto s = ss.c_str();
	GLuint hShader = glCreateShader(type);
	glShaderSource(hShader, 1, &s, nullptr);
	glCompileShader(hShader);
	return hShader;
}
