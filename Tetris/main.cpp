#include <iostream>
#include <Windows.h>

const int screenWidth{120};
const int screenHeight{30};

int main(){
	HANDLE screenConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD byteWritten{};


	if(screenConsole == INVALID_HANDLE_VALUE){
		std::cerr << "Could make console\n";
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(screenConsole)){
		std::cerr << "SetConsoleActiveScreenBuffer failed\n";
		CloseHandle(screenConsole);
		return 1;
	}
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
	if (!GetConsoleScreenBufferInfo(screenConsole, &screenInfo)) {
		std::cerr << "GetConsoleScreenBufferInfo failed\n";
		CloseHandle(screenConsole);
		return 1;
	}

	bool gameOver{false};
	bool quitGame{false};

	char screen[screenWidth * screenHeight];


	while(!gameOver){

		// screen clearing
		for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = ' ';

		// borders 
		for(int i{}; i < screenWidth; i++) {
			screen[i] = '#';
		//	screen[2 * screenWidth + i] = '=';
		}














		WriteConsoleOutputCharacter(screenConsole, screen, screenWidth * screenHeight,{0,0},&byteWritten);
		quitGame = (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) != 0;
		if(quitGame) gameOver = true;

	}




	CloseHandle(screenConsole);

	return 0;

}
