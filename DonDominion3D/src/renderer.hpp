#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



class Renderer {
	public:
		bool init();
		void run();

	private:
		GLFWwindow *window{};
		uint16_t width{1000};
		uint16_t height{800};
};
