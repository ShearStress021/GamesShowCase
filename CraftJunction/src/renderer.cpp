#include "renderer.hpp"



Renderer::Renderer(){

}

Renderer::~Renderer(){
	cleanUp();
}


void Renderer::cleanUp(){

	if(window){
		if(window)glfwDestroyWindow(window);
	}
	glfwTerminate();

}

bool Renderer::initVulkan(){
	return true;
}



bool Renderer::init(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(1000, 800, "Craft Junction",nullptr, nullptr);

	if(!window){
		std::cerr << "window not create" << '\n';
		return false;
	}
	if(!initVulkan()){
		std::cerr << "Init Vulkan created!!" << '\n';
		return false;
	}

	return true;
}

void Renderer::run(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}


}





