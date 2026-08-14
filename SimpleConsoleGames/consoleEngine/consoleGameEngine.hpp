#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <atomic>
#include <chrono>
#include <thread>



class ConsoleGameEngine {

	public:
		ConsoleGameEngine() {
			handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::string title {"Default"};
			gameName  = title.data();
		}
		bool CreateConsole(std::uint8_t width, std::uint8_t height){
			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Couldn't make value\n";
				return false;
			}

			if (!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "SetConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return false;

			}
			if (!GetConsoleScreenBufferInfo(handleConsole, &screenInfo)) {
				std::cerr << "GetConsoleScreenBufferInfo failed\n";
				CloseHandle(handleConsole);
				return false;
			}

			screenWidth = width;
			screenHeight = height;

			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{(short) screenWidth, (short)screenHeight};
			if(!SetConsoleScreenBufferSize(handleConsole, bufferSize)){
				std::cerr << "SetConsoleScreenBufferInfo failed\n";
				CloseHandle(handleConsole);
				return false;

			}

			windowRect = {0, 0, (short)(screenWidth -1), (short)(screenHeight- 1)};
			if(!SetConsoleWindowInfo(handleConsole,TRUE,&windowRect)){
				std::cerr << "SetConsoleWindowInfo failed\n";
				return false;
			}

			screen = new CHAR_INFO[screenWidth * screenHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);







			return true;
		}

		void GameInit(){
			GamePlay();
		}


		~ConsoleGameEngine(){
			CloseHandle(handleConsole);
			delete screen;
			
		}


	private:
		void GamePlay(){
			
			std::this_thread::sleep_for(std::chrono::milliseconds(200));



			char s[256];
			//std::snprintf(n[screenWidth + 5], std::size(screen) - (screenWidth - 5), 
								//	"SNAKEHEAD X: Y: %d %d", snakeHead.x, snakeHead.y);
			//swprintf_s(s, 256, L"OneLoneCoder.com - Console Game Engine - %s - FPS: %3.2f", m_sAppName.c_str(), 1.0f / fElapsedTime);
			//swprintf_s(s, 256, L"OneLoneCoder.com - Console Game Engine - %s - FPS: %3.2f", m_sAppName.c_str(), 1.0f / fElapsedTime);
			std::snprintf(s,std::size(s),"My Game %s",gameName);
			SetConsoleTitle(s);
			WriteConsoleOutput(handleConsole, screen, {(short)screenWidth,(short)screenHeight}, {0,0}, &windowRect);
			//WriteConsoleOutputCharacter(handleConsole,,1,{0,0},&byteWritten);



		}

		

	private:
		std::uint8_t screenWidth{};
		std::uint8_t screenHeight{};
		HANDLE handleConsole{};
		CHAR_INFO *screen;
		char*  gameName;
		SMALL_RECT windowRect{};
		DWORD byteWritten{};
		char text{'A'};
		CONSOLE_SCREEN_BUFFER_INFO screenInfo{};

		static std::atomic<bool> activeAtom;
		



};






