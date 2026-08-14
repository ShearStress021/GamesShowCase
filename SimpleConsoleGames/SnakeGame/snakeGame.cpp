#include "../consoleEngine/consoleGameEngine.hpp"

int main(){

	ConsoleGameEngine game{};
	if(game.CreateConsole(130,30))
		game.GameInit();
	std::cout << "Hello, World\n";
	return 0;
}
