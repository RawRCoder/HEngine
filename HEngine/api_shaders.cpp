#include "api_shaders.h"
#include <ioutils.h>

GLuint LoadShaderFromFile(const wchar_t* fileName, GLenum type)
{
	auto s = ReadToEndAsString(fileName);
	GLuint hShader = glCreateShader(type);
	glShaderSource(hShader, 1, &s, nullptr);
	glCompileShader(hShader);
	delete[] s;
	return hShader;
}
