#include <iostream>
#include <ranges>
#include <vector>
#include <windows.h>
#include <cstdint>
#include <chrono>
#include <thread>


struct Vector3 {
	float x, y, z;
};

struct Vec2 {
	float psi, phi;

};

struct PlayerView {
	Vector3 pos{};
	Vec2 vw{};
};



class Minecraft {
	private:
		HANDLE handleConsole{};
		SMALL_RECT windowRect{};
		std::uint8_t windowWidth{};
		std::uint8_t windowHeight{};
		CHAR_INFO* screen{};
		bool running{false};


	public:

		Minecraft(){
			handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			windowWidth = 130;
			windowHeight = 30;



		}
		int  createConsoleWindow(std::uint8_t width, std::uint8_t height){
			windowWidth = width;
			windowHeight = height;

			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Couldn't make handle Console\n";
				return 1;
			}
			if(!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "Set ConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return 1;
			}

			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{(short) windowWidth, (short) windowHeight};
			if(!SetConsoleScreenBufferSize(handleConsole, bufferSize)){
				std::cerr << "Set Console Screen Buffer Size failed\n";
				CloseHandle(handleConsole);
				return 1;
			}

			CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
			if(!GetConsoleScreenBufferInfo(handleConsole, &screenInfo)){
				std::cerr << "GetConsoleScreenBufferInfo Failed\n";
				CloseHandle(handleConsole);
				return 1;
			}

			windowRect = {0,0, (short)(windowWidth- 1), (short)(windowHeight-1 )};
			if(!SetConsoleWindowInfo(handleConsole, TRUE, &windowRect)){
				std::cerr << "Set Console Window Info\n";
				return 1;
			}

			screen = new CHAR_INFO[windowWidth * windowHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * windowWidth * windowHeight);
			return 0;
		}


		void renderConsole(){

			while(!running){
				WriteConsoleOutput(handleConsole, screen, 
						{(short)windowWidth, (short)windowHeight},{0,0}, &windowRect);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) running = true;


			}
		}

		PlayerView initVeiw(){
			PlayerView posVw{};

			posVw.pos.x = 5;
			posVw.pos.y = 5;
			posVw.pos.z = 4 + 1.5;

			posVw.vw.psi = 0;
			posVw.vw.phi = 0;
			return posVw;
		}

};


int main(){

	Minecraft game{};
	game.createConsoleWindow(130, 30);
	game.renderConsole();

	std::cout << "Hello, World\n";
	return 0;
}
