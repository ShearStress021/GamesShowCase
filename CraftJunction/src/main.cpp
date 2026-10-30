#include "renderer.hpp"


int main(){
	Renderer app{};
	if(app.init()){
		app.run();
	}
	return 0;
}
