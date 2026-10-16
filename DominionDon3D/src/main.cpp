#include "renderer.hpp"




int main(void){
	Renderer game{};

	if(game.init()){
		game.run();
	}
	return 0;
}
