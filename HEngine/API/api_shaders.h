#pragma once
#include <string>

#define GLEW_STATIC
#define GLFW_STATIC
#include <GL/glew.h>

GLuint LoadShaderFromFile(const wchar_t* fileName, GLenum type);