#include "renderer.hpp"
#include <iostream>


Renderer::Renderer(){

}

Renderer::~Renderer(){
	cleanUp();
}

void Renderer::cleanUp(){
	if(window)glfwDestroyWindow(window);
	glfwTerminate();
}
bool Renderer::init(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height,"Don dominion 3d",nullptr, nullptr);

	if(!window){
		showError("GLFW window failed to create");
		return false;
	}

	if(!initVulkan()){
		showError("Vulkan Error!!!");
		return false;
	}
	return true;
}

void Renderer::run(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}

}


void Renderer::showError(const char* msg) const {
	throw std::runtime_error(msg);
}

bool Renderer::initVulkan(){

	if(!createInstance()){
		showError("Vulkan  instance not created!!!");
		return false;
	}

	return true;
}

bool Renderer::createInstance(){

	VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = appName,
		.apiVersion = vulkanVersion
	};
	uint32_t instExtCount{};


	return true;
}
