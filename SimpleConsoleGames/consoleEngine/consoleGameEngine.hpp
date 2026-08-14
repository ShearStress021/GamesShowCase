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
	public:
		int CreateConsole(std::uint8_t width, std::uint8_t height){
			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Couldn't make value\n";
				return 1;
			}

			if (!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "SetConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return 1;

			}
			if (!GetConsoleScreenBufferInfo(handleConsole, &screenInfo)) {
				std::cerr << "GetConsoleScreenBufferInfo failed\n";
				CloseHandle(handleConsole);
				return 1;
			}

			screenWidth = width;
			screenHeight = height;

			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{(short) screenWidth, (short)screenHeight};
			if(!SetConsoleScreenBufferSize(handleConsole, bufferSize)){
				std::cerr << "SetConsoleScreenBufferInfo failed\n";
				CloseHandle(handleConsole);
				return 1;

			}

			windowRect = {0, 0, (short)(screenWidth -1), (short)(screenHeight- 1)};
			if(!SetConsoleWindowInfo(handleConsole,TRUE,&windowRect)){
				std::cerr << "SetConsoleWindowInfo failed\n";
				return 1;
			}

			screen = new CHAR_INFO[screenWidth * screenHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);


			return 0;
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

			while(running){
				std::this_thread::sleep_for(std::chrono::milliseconds(200));



				char s[256];
				std::snprintf(s,std::size(s),"My Game %s",gameName);
				SetConsoleTitle(s);
				WriteConsoleOutput(handleConsole, screen, {(short)screenWidth,(short)screenHeight}, {0,0}, &windowRect);

			}
			
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

		static std::atomic<bool> running;
		



};






