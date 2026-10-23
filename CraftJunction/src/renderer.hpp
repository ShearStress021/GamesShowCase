#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>



class Renderer {
	public:
		Renderer();
		~Renderer();
		bool init();
		void run();
	private:
		void cleanUp();

		// vulkan
		bool initVulkan();
	
	private:
		GLFWwindow *window{nullptr};
		uint16_t width{};
		uint16_t height{};



};
