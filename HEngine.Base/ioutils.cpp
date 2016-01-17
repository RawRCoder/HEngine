#include "ioutils.h"
#include <fstream>

std::string ReadToEndAsString(const std::wstring& fileName)
{
	const int BUFFER_SIZE = 4096;
	std::string s = "";

	std::ifstream f;
	f.open(fileName);
	{
		char buffer[BUFFER_SIZE+1];
		buffer[BUFFER_SIZE] = 0;
		while (f && f.is_open())
		{
			f.read(buffer, BUFFER_SIZE);
			auto len = f.gcount();
			if (len < BUFFER_SIZE)
				buffer[len] = 0;
			s += buffer;
			if (len < BUFFER_SIZE)
				break;
		}
	}
	f.close();
	return s;
}
