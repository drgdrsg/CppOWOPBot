#pragma once
#include <Windows.h>
#include <string>

namespace ConsoleHelper
{
	DWORD GetNumCharsInConsoleBuffer();
	DWORD ReadConsoleBuffer(char* buffer, DWORD bufsize, COORD firstChar = { 0 });
	DWORD ReadConsoleAttributes(uint16_t* buffer, DWORD bufsize, COORD firstChar);
	void GetConsoleRect(int &left, int &top, int & width, int & height);
	std::string GetTerminalSmapshot();
};

