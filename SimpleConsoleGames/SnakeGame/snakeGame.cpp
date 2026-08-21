#include "../consoleEngine/consoleGameEngine.hpp"


class SnakeGame : public ConsoleGameEngine {

	public:
		virtual bool CustomGame(){


			for (int i{}; i < screenWidth * screenHeight; i++) {
				screen[i].Char.UnicodeChar = ' ';
				screen[i].Attributes = FOREGROUND_RED;
			}

			for(int i{}; i < screenWidth; i++){
				screen[i].Char.UnicodeChar  = '=';
				screen[i].Attributes = FOREGROUND_GREEN;
			}


			return true;
		}


};

int main(){

	SnakeGame game{};
	game.CreateConsole(130,30);
    game.GameInit();
	std::cout << "Hello, World\n";
	return 0;
}
