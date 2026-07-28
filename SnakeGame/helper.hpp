#pragma once
#include <Windows.h>



struct ConsoleHandle {

	HANDLE value {INVALID_HANDLE_VALUE};

	~ConsoleHandle(){
		if(value != nullptr && value != INVALID_HANDLE_VALUE) CloseHandle(value);
	}

	ConsoleHandle(const ConsoleHandle&) = delete;
	ConsoleHandle& operator=(const ConsoleHandle&) = delete;

};

