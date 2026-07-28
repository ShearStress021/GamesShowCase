#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <thread>
#include <string>
#include <algorithm>
#include "helper.hpp"


using namespace std::chrono_literals;


struct Snake {
	int x;
	int y;
};

constexpr int screenWidth{150};
constexpr int screenHeight{38};


enum class Direction{LEFT, RIGHT,UP,DOWN};

Direction direction{Direction::LEFT};


void setColor(int color, HANDLE &handle){
	
	SetConsoleTextAttribute(handle, color);

}


void setConsoleSize(int width, int height, HANDLE& handle)
{
	SMALL_RECT tempRect{0,0,1,1};
	SetConsoleWindowInfo(handle, TRUE, &tempRect);


	COORD bufferSize{};
	bufferSize.X = (SHORT)width;
	bufferSize.Y = (SHORT)height;

	SetConsoleScreenBufferSize(handle, bufferSize);

	SMALL_RECT windowRect{};
	windowRect.Left = 0;
	windowRect.Top = 0;
	windowRect.Right = (SHORT)(width - 1);
	windowRect.Bottom =(SHORT)(height - 1);

	SetConsoleWindowInfo(handle, TRUE,&windowRect);
}

int main(){

	ConsoleHandle screenConsole{CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
			CONSOLE_TEXTMODE_BUFFER, NULL)};
	DWORD byteWritten{};
	DWORD attributesWritten{};


	if(screenConsole.value == INVALID_HANDLE_VALUE){
		std::cerr << "Could make console\n";
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(screenConsole.value)){
		std::cerr << "SetConsoleActiveScreenBuffer failed\n";
		CloseHandle(screenConsole.value);
		return 1;
	}
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
	if (!GetConsoleScreenBufferInfo(screenConsole.value, &screenInfo)) {
		std::cerr << "GetConsoleScreenBufferInfo failed\n";
		CloseHandle(screenConsole.value);
		return 1;
	}



	setConsoleSize(screenWidth, screenHeight, screenConsole.value);
	setColor(FOREGROUND_GREEN, screenConsole.value);
	



	bool gameOver{false};
	bool quitGame{false};
	bool isDead{false};

	char screen[screenWidth * screenHeight];
	WORD color[screenWidth * screenHeight];

	std::vector<Snake>  snake {{60, 15}, {61, 15}, {62, 15}};

	bool keyLeft{false};
	bool keyUp{false};
	bool keyRight{false};
	bool keyDown{false};

	char snakesHead{'>'};
	int snakesDirection{3};

	int foodX{60};
	int foodY{20};
	int score{};



	//auto timeNow = std::chrono::system_clock::now();



	while(!gameOver){

		// snake Movement
		auto timeNow = std::chrono::system_clock::now();

		while((std::chrono::system_clock::now()- timeNow) <  std::chrono::milliseconds(120)){
			keyRight = (GetAsyncKeyState((unsigned char)('\x27')) & 0x8000) != 0;
			keyLeft = (GetAsyncKeyState((unsigned char)('\x25')) & 0x8000) != 0;
			keyUp = (GetAsyncKeyState((unsigned char)('\x26')) & 0x8000) != 0;
			keyDown = (GetAsyncKeyState((unsigned char)('\x28')) & 0x8000) != 0;


			if(keyLeft && direction != Direction::RIGHT)
				direction = Direction::LEFT;
			else if(keyRight && direction != Direction::LEFT)
				direction = Direction::RIGHT;
			else if(keyDown && direction != Direction::UP)
				direction = Direction::DOWN;
			else if(keyUp && direction != Direction::DOWN)
				direction = Direction::UP;

		}
		Snake snakeHead = snake.front();

		switch(direction){
			case Direction::UP:
				snakeHead.y --;
				break;
			case Direction::RIGHT:
				snakeHead.x ++;
				break;
			case Direction::DOWN:
				snakeHead.y++;
				break;
			case Direction::LEFT:
				snakeHead.x--;
				break;


		}
		snake.insert(snake.begin(), snakeHead);

		switch(direction){
			case Direction::RIGHT:
				snakesHead = '>';
				break;
			case Direction::LEFT:
				snakesHead = '<';
				break;
			case Direction::UP:
				snakesHead = '^';
				break;
			case Direction::DOWN:
				snakesHead = 'v';
				break;

		}

		std::this_thread::sleep_for(150ms);

		if(snakeHead.x < 0 ||  snakeHead.x >= screenWidth)
			isDead = true;
		if(snakeHead.y < 3 || snakeHead.y >= screenHeight)
			isDead = true;


		if(snakeHead.x == foodX && snakeHead.y == foodY){
			score++;

			while(screen[foodY * screenWidth + foodX] != ' '){
				foodX = rand() % screenWidth;
				foodY = (rand() % screenHeight) + 3;

			}

			snake.push_back({snake.back().x , snake.back().y});
		}

		// delete last
		snake.pop_back();


		// screen clearing
		for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = ' ';

		std::string status = "Snake X: " + std::to_string(snakeHead.x) +  "Y: " + std::to_string(snakeHead.y);

		std::snprintf(&screen[screenWidth + 5], std::size(screen) - (screenWidth - 5), 
				"SNAKEHEAD X: Y: %d %d", snakeHead.x, snakeHead.y);
		
		std::snprintf(&screen[screenWidth + 40], std::size(screen) - (screenWidth - 5), 
				"SNAKE SCORE: %d ",  score);

	


		for(int i = 0; i < screenWidth; i++){
			screen[i] = '=';
			screen[2 * screenWidth + i] = '=';
		}

		// snake body
		for(size_t i{1}; i < snake.size(); i++){
			Snake prev = snake[i - 1];
			Snake s = snake[i];
			char bodyChar = 'o';

			screen[s.y * screenWidth + s.x] = bodyChar;
		//	color[s.y * screenWidth + s.x] = FOREGROUND_GREEN;

		}


		screen[snake.front().y * screenWidth + snake.front().x] = isDead ? 'X':  snakesHead;


		screen[foodY * screenWidth + foodX] = '@';



		WriteConsoleOutputCharacter(screenConsole.value, screen, screenWidth * screenHeight,{0,0},&byteWritten);
		//WriteConsoleOutputAttribute(screenConsole.value, color, screenWidth * screenHeight,{0,0},&attributesWritten);
		quitGame = (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) != 0;
		if(quitGame || isDead) gameOver = true;

	}

	return 0;
}
