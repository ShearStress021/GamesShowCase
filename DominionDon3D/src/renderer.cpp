#include "renderer.hpp"



bool Renderer::init(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height,"Don dominion 3d",nullptr, nullptr);

	if(!window){
		return false;
	}
	return true;
}

void Renderer::run(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
