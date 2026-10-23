
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <string>




class Renderer {
	public:
		Renderer();
		~Renderer();
		bool init();
		void run();
		void cleanUp();

	private:
		GLFWwindow *window{};
		uint16_t width{1280};
		uint16_t height{720};

		constexpr static char appName[] = "FaveleTusle";
		constexpr static uint32_t vulkanVersion {VK_API_VERSION_1_4}; 

		// Vulkan Item

		VkInstance instance{VK_NULL_HANDLE};


	private:
		//  
		void showError(const char* msg) const;

		// Vulkan Methods
		// starter
		bool initVulkan();
		bool createInstance();
		bool createSurface();
};
