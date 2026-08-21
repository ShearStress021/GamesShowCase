#include <iostream>
#include <Windows.h>
#include <cstdint>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>


struct Point {
	int x{};
	int y{};
};

enum class Direction{
	LEFT, RIGHT, UP, DOWN
};

class SnakeGame {
	private:
		HANDLE handleConsole{};
		std::uint8_t screenWidth{};
		std::uint8_t screenHeight{};
		SMALL_RECT windowRect{};
		CHAR_INFO* screen{};
		DWORD byteWritten{};
		std::atomic<bool> gameOver{false};
		std::mutex mtx{};
		std::vector<Point> snake{{50,20}, {51,20}};
		char snakeHead{'<'};
		Direction direction{Direction::LEFT};
		Point food{40,23};
		bool keyRight,keyLeft,keyUp, keyDown, guitGamem, isDead{false};

		

	public:
		SnakeGame(){
			screenWidth = 130;
			screenHeight = 35;
			handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		int createWindow(std::uint8_t width, std::uint8_t height){
			screenWidth = width;
			screenHeight = height;

			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Could make Console\n";
				return 1;
			}
			if(!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "Set ConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return 1;
			}


			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{};
			bufferSize = {(short)screenWidth, (short)screenHeight};
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

			windowRect = {0,0, (short)(screenWidth - 1), (short)(screenHeight -1 )};

			if(!SetConsoleWindowInfo(handleConsole, TRUE, &windowRect)){
				std::cerr << "Set Console Window Info\n";
				return 1;
			}

			screen = new CHAR_INFO[screenWidth * screenHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

			return 0;

		}

		void inputThread(){
			while(!gameOver){
				std::lock_guard<std::mutex> lock(mtx);

				if (GetAsyncKeyState((unsigned char)('\x27')) & 0x8000) direction = Direction::RIGHT;
				else if (GetAsyncKeyState((unsigned char)('\x25')) & 0x8000) direction = Direction::LEFT;
				else if (GetAsyncKeyState((unsigned char)('\x26')) & 0x8000) direction = Direction::UP;
				else if (GetAsyncKeyState((unsigned char)('\x28')) & 0x8000) direction = Direction::DOWN;
				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) gameOver = true;

			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		void renderer(){

			while(!gameOver){
				update();
				// screen clearing  
				for(int i{}; i < screenWidth * screenHeight; i++) {
					screen[i].Char.UnicodeChar= ' ';
					screen[i].Attributes = FOREGROUND_GREEN;
				}
					

				// boarder 
				for(int i {}; i < screenWidth; i++){
					screen[i].Char.UnicodeChar = '=';
					screen[2* screenWidth + i].Char.UnicodeChar= '=';
				}

				for(size_t i{1}; i < snake.size(); i++){
					Point s = snake[i];
					screen[s.y * screenWidth + s.x].Char.UnicodeChar = isDead ? 'Q' : 'o';
				}

				//
				screen[snake.front().y * screenWidth + snake.front().x].Char.UnicodeChar = isDead ? 'X':  snakeHead;


				screen[food.y * screenWidth + food.x].Char.UnicodeChar = '@';
		





				WriteConsoleOutput(handleConsole, screen, 
						{(short)screenWidth , (short)screenHeight}, {0,0}, &windowRect);
				if(isDead) gameOver = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));


			}

		}


		~SnakeGame(){
			gameOver = true;
			delete[] screen;
			CloseHandle(handleConsole);
		}
	private:

		void update(){
			Direction dir;

			{
				std::lock_guard<std::mutex> lock(mtx);
				dir = direction;

			}
			Point head = snake.front();

			switch(dir){
				case Direction::LEFT:
					head.x--;
					snakeHead = '<';
					break;
				case Direction::RIGHT:
					head.x++;
					snakeHead = '>';
					break;
				case Direction::UP:
					head.y--;
					snakeHead = '^';
					break;
				case Direction::DOWN:
					head.y++;
					snakeHead = 'v';
					break;
			}


			snake.insert(snake.begin(), head);

			eatingFood();

			if(head.x < 0 || head.x >= screenWidth) isDead = true;
			if(head.y < 3 || head.y >= screenHeight) isDead = true;
			snake.pop_back();

		}

		void eatingFood(){
			Point head = snake.front();

			if (head.x == food.x && head.y == food.y){

				while(screen[food.y * screenWidth + food.x].Char.AsciiChar != ' '){
					food.x = rand() % screenWidth;
					food.y = (rand() % screenHeight) + 3;
				}

				snake.push_back({snake.back().x, snake.back().y});
			}

		}
		


};


int main(){
	SnakeGame game{};
	game.createWindow(130, 30);

	std::thread gameLoop(&SnakeGame::renderer, &game);
	std::thread inputThread(&SnakeGame::inputThread, &game);

	gameLoop.join();
	inputThread.join();
	return 0;
}
