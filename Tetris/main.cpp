#include <iostream>
#include <Windows.h>
#include <cstdint>
#include <string>

class TetrisGame {
	private:
		HANDLE screenConsole{};
		static const std::uint8_t screenWidth{130};
		static const std::uint8_t screenHeight{30};
		char screen[screenWidth * screenWidth];
		DWORD byteWritten{};
		SMALL_RECT windowRect{};
		bool running{false};
		std::string pieces[7];
		std::uint8_t currentPiece{3};
		std::uint8_t fieldWidth{12};
		std::uint8_t fieldHeight{18};

		std::uint8_t currentX{0};
		std::uint8_t currentY{0};
		
	
	private:
		int rotatePiece(int x, int y, int r){
			int p{0};

			switch(r % 4){
				case 0:
					p = y * 4 + x;
					break;
				case 1:
					p = 12 + y -(x * 4);
					break;
				case 2:
					p = 15 - (y * 4) - x;
					break;
				case 3:
					p = 3 - y + (x * 4);
					break;
			}
			return p;

		}
		
	public:

		TetrisGame(){
			screenConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
					NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

			pieces[0].append("..X...X...X...X.");
			pieces[1].append(".....XX..XX.....");
			pieces[2].append("..X..XX...X.....");
			pieces[3].append("..X..XX..X......");
			pieces[4].append(".X...XX...X.....");
			pieces[5].append(".X...X....XX....");
			pieces[6].append("..X...X..XX.....");

			currentX = fieldWidth / 2;
		}

		int createConsole(){
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


			SMALL_RECT windowRect{0,0,1,1};
			SetConsoleWindowInfo(screenConsole, TRUE, &windowRect);

			COORD bufferSize{(short)screenWidth, (short)screenHeight};
			SetConsoleScreenBufferSize(screenConsole, bufferSize);

			windowRect = {0,0,(short)screenWidth - 1, (short)screenHeight -1};
			SetConsoleWindowInfo(screenConsole,TRUE,&windowRect);
			return 0;

		}
		void renderConsole(){
			while(!running){
				for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = ' ';

				for(int i{}; i < screenWidth; i++){
					screen[i] = '=';
				}

				//currentPiece = rand() % 7;
				
				// Draw a piece
				for(int x{}; x < 4; x++){
					for(int y{}; y < 4; y ++){
						if(pieces[currentPiece][y] != '.'){
							screen[(currentY + y + 2) * screenWidth + (currentX + x + 2)] = currentPiece + 65;
						}
							
					}

				}





				WriteConsoleOutputCharacter(screenConsole,screen,screenWidth * screenHeight, {0,0}, &byteWritten);
				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) running = true;

			}


		}

		~TetrisGame(){
			CloseHandle(screenConsole);
		}






};


int main(){

	TetrisGame game{};
	game.createConsole();
	game.renderConsole();
	return 0;

}
