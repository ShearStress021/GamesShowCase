#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>
#include <string>


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

	COORD size{screenWidth, screenHeight};
	SetConsoleScreenBufferSize(screenConsole, size);


	bool gameOver{false};
	bool quitGame{false};
	bool isDead{false};

	char screen[screenWidth * screenHeight];

	std::vector<Snake>  snake {{60, 15}, {61, 15}, {62, 15}};

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

		while((std::chrono::system_clock::now()- timeNow) <  std::chrono::milliseconds(120)){
			//keyRight = (GetAsyncKeyState((unsigned char)('\x27')) & 0x8000) != 0;
			keyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
			keyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
			//keyLeft = (GetAsyncKeyState((unsigned char)('\x25')) & 0x8000) != 0;
			keyUp = (GetAsyncKeyState((unsigned char)('\x26')) & 0x8000) != 0;
			keyDown = (GetAsyncKeyState((unsigned char)('\x28')) & 0x8000) != 0;


			if(keyLeft && sDir != RIGHT)
				sDir = LEFT;
			else if(keyRight && sDir != LEFT)
				sDir = RIGHT;
			else if(keyDown && sDir != UP)
				sDir = DOWN;
			else if(keyUp && sDir != DOWN)
				sDir = UP;

	//		if(keyRight && !keyRightOld){
	//			snakesDirection ++;
	//			if(snakesDirection == 4) snakesDirection = 0; }
	//		if(keyLeft && !keyLeftOld){
	//			snakesDirection --;
	//			if(snakesDirection == -1) snakesDirection = 3;
	//		}


			//keyLeftOld = keyLeft;
			//
			//keyRightOld = keyRight;


		}
		Snake snakeHead = snake.front();

		switch(sDir){
			case UP:
				snakeHead.y --;
				break;
			case RIGHT:
				snakeHead.x ++;
				break;
			case DOWN:
				snakeHead.y++;
				break;
			case LEFT:
				snakeHead.x--;
				break;


		}
		snake.insert(snake.begin(), snakeHead);

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

		std::this_thread::sleep_for(300ms);

		if(snakeHead.x < 0 ||  snakeHead.x >= screenWidth)
			isDead = true;
		if(snakeHead.y < 3 || snakeHead.y >= screenHeight)
			isDead = true;

		// delete last
		snake.pop_back();


		// screen clearing
		for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = ' ';


		wsprintf(&screen[screenWidth + 5], "www.OneLoneCoder.com - S N A K E ! !                SCORE: %d %d", 
				snakeHead.x, snakeHead.y);
		wsprintf(&screen[screenWidth + 10], "Pressed keys %d %d", keyLeft, keyRight);





		for(int i = 0; i < screenWidth; i++){
			screen[i] = '=';
			screen[2 * screenWidth + i] = '=';
		}

		// snake body
		for(size_t i{1}; i < snake.size(); i++){
			Snake s = snake[i];
			screen[s.y * screenWidth + s.x] = '-';

		}


		screen[snake.front().y * screenWidth + snake.front().x] = snakesHead;

	






		WriteConsoleOutputCharacter(screenConsole, screen, screenWidth * screenHeight,{0,0},&byteWritten);
		quitGame = (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) != 0;
		if(quitGame || isDead) gameOver = true;

	}



	return 0;
}
