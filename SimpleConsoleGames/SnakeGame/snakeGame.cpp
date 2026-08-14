#include "../consoleEngine/consoleGameEngine.hpp"


class SnakeGame : public ConsoleGameEngine {

};

int main(){

	SnakeGame game{};
	game.CreateConsole(130,30);
    game.GameInit();
	std::cout << "Hello, World\n";
	return 0;
}
