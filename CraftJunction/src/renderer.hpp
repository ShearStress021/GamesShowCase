#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdint>
#include <iostream>
#include <vector>



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

		bool createInstance();
		bool createSurface();
		VkPhysicalDevice findPhysicalDevice();

		bool findGraphicQueue();
		bool createDevice(VkPhysicalDevice physicalDevice);



	
	private:
		GLFWwindow *window{nullptr};
		constexpr static uint16_t width{1020};
		constexpr static uint16_t height{720};
		constexpr static VkFormat swapchanFormat{VK_FORMAT_B8G8R8A8_SRGB};
		


		VkInstance instance{VK_NULL_HANDLE};
		VkSurfaceKHR surface{VK_NULL_HANDLE};
		
		// Devices
		VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
		VkDevice device{VK_NULL_HANDLE};

		//queue family
		uint32_t gfxQueueFamIdx{UINT32_MAX};
		VkQueue gfxQueue{VK_NULL_HANDLE};




};
