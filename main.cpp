#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>



int main(){
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if(hConsole == INVALID_HANDLE_VALUE){
		std::cerr << "Could make console\n";
		return 1;

	}

	if (!SetConsoleActiveScreenBuffer(hConsole)){
		std::cerr << "SetConsoleActiveScreenBuffer failed\n";
		CloseHandle(hConsole);
		return 1;

	}
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
	if (!GetConsoleScreenBufferInfo(hConsole, &screenInfo)) {
		std::cerr << "GetConsoleScreenBufferInfo failed\n";
		CloseHandle(hConsole);
		return 1;

	}

	SHORT width = screenInfo.dwSize.X;
	SHORT height = screenInfo.dwSize.Y;

	COORD pos = { 0, 0   };
	std::string text = "A";
	std::string start = " ";
	DWORD bytesWritten = 0;
	bool gameOver = false;
	bool keys[5];

	while(pos.X < width){
		int currentX{};
		int currentY{};

		for(uint8_t i{}; i < 4; i++){
			keys[i] = (GetAsyncKeyState((unsigned char)("\x25\x26\x27\x28\x20"[i])) & 0x8000) != 0;
			currentX += (keys[0]) ? -1 : 0;
			currentY += (keys[1]) ? -1 : 0;
			currentX += (keys[2]) ? 1 : 0;
			currentY += (keys[3]) ? 1 : 0;

															}

		DWORD len = static_cast<DWORD>(text.size());
		WriteConsoleOutputCharacter(hConsole,start.c_str(),1,pos,&bytesWritten);

		pos.X += currentX;
		pos.Y += currentY;

		WriteConsoleOutputCharacter(hConsole,text.c_str(),len,pos,&bytesWritten);
		text += "-";
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		//
		//
		//
	}
	Sleep(2000);
	CloseHandle(hConsole);

													return 0;


	
	std::cout << "Hello, World\n";
	return 0;
}
