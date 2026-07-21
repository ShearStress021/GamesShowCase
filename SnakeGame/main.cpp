#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>
using namespace std::chrono_literals;


struct Snake {
	int x;
	int y;
};

const int screenWidth{120};
const int screenHeight{30};

int snakeTailX[100];
int snakeTailY[100];
int snakeTailLen;

enum snakeDirection {STOP =0, LEFT, RIGHT,UP,DOWN};

snakeDirection sDir{LEFT};

int main(){
	HANDLE screenConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, 
			CONSOLE_TEXTMODE_BUFFER, NULL);
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

	std::vector<Snake>  snake {{100, 15}, {101, 15}, {102, 15}};

	bool keyLeft{false};
	bool keyUp{false};
	bool keyRight{false};
	bool keyRightOld{false};
	bool keyLeftOld{false};
	bool keyDown{false};

	char snakesHead{'>'};
	int snakesDirection{3};



	//auto timeNow = std::chrono::system_clock::now();



	while(!gameOver){

		// snake Movement
		auto timeNow = std::chrono::system_clock::now();

		while((std::chrono::system_clock::now()- timeNow) < ((snakesDirection % 2 == 1) ? 
					std::chrono::milliseconds(120ms) : std::chrono::milliseconds(200ms))){
			keyRight = (GetAsyncKeyState((unsigned char)('\x27')) & 0x8000) != 0;
			keyLeft = (GetAsyncKeyState((unsigned char)('\x25')) & 0x8000) != 0;
			keyUp = (GetAsyncKeyState((unsigned char)('\x26')) & 0x8000) != 0;
			keyDown = (GetAsyncKeyState((unsigned char)('\x28')) & 0x8000) != 0;


			//if(keyLeft && sDir != RIGHT)
			//	sDir = LEFT;
			//else if(keyRight && sDir != LEFT)
			//	sDir = RIGHT;
			//else if(keyDown && sDir != UP)
			//	sDir = DOWN;
			//else if(keyUp && sDir != DOWN)
				//sDir = UP;

			if(keyRight && !keyRightOld){
				snakesDirection ++;
				if(snakesDirection == 4) snakesDirection = 0;
			}
			if(keyLeft && !keyLeftOld){
				snakesDirection --;
				if(snakesDirection == -1) snakesDirection = 3;
			}

			keyLeftOld = keyLeft;
			keyRightOld = keyRight;


		}
		Snake snakeHead = snake.front();

		switch(snakesDirection){
			case 0:
				snakeHead.y --;
				break;
			case 1:
				snakeHead.x ++;
				break;
			case 2:
				snakeHead.y++;
				break;
			case 3:
				snakeHead.x--;
				break;


		}
		snake.insert(snake.begin(), snakeHead);
		snake.pop_back();

		switch(sDir){
			case RIGHT:
				snakesHead = '>';
				break;
			case LEFT:
				snakesHead = '<';
				break;
			case UP:
				snakesHead = '^';
				break;
			case DOWN:
				snakesHead = 'v';
				break;

		}

		// screen clearing
		for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = ' ';

		for(int i = 0; i < screenWidth; i++){
			screen[i] = L'=';
			screen[2 * screenWidth + i] = L'=';
		}
	



		// snake body
		for(size_t i{1}; i < snake.size(); i++){
			Snake s = snake[i];
			screen[s.y * screenWidth + s.x] = 'o';

		}


		screen[snake.front().y * screenWidth + snake.front().x] = '@';

	






		WriteConsoleOutputCharacterA(screenConsole, screen, screenWidth * screenHeight,{0,0},&byteWritten);
		quitGame = (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) != 0;
		if(quitGame) gameOver = true;

	}



	return 0;
}
