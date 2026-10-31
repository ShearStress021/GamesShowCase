#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>



struct VmaAllocator_T;
typedef struct VmaAllocator_T* VmaAllocator;
struct VmaAllocation_T;
typedef struct VmaAllocation_T* VmaAllocation;

struct FrameResources {
	VkCommandPool commandPool{VK_NULL_HANDLE};
	VkCommandBuffer commandbuffer{VK_NULL_HANDLE};
	VkSemaphore imageAcquiredSemaphore{VK_NULL_HANDLE};


};

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

		bool initializeVMA();
		bool createSwapchain(uint32_t width, uint32_t height);
		void destroySwapchain();
		

		// pipeline
		VkPipeline createGraphicsPipeline();

		bool createSyncResources();
		bool createCommandBuffers();
		void waitOnTimeline(VkDevice device,VkSemaphore timeline, uint64_t value);
		void display();


		

		// shader module
		VkShaderModule createShaderModule(const std::string &filename) const; 
		bool createShader();

		static std::vector<char> readTextFile(const std::string &filename) {

			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if(!file.is_open()){
				throw std::runtime_error("failed to open file");
			}
			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);
			file.seekg(0);
			file.read(buffer.data(), fileSize);
			file.close();
			return buffer;

		}


	





	
	private:
		GLFWwindow *window{nullptr};
		uint16_t width{800};
		uint16_t height{600};
		constexpr static VkFormat swapchainFormat{VK_FORMAT_B8G8R8A8_SRGB};
		constexpr static VkFormat depthFormat{ VK_FORMAT_D32_SFLOAT   };
		constexpr static uint32_t MaxFramesInFlight{ 2  };
		uint64_t frameIdx{};
		uint64_t nextSignalValue{MaxFramesInFlight + 1};


		
		VkInstance instance{VK_NULL_HANDLE};
		VkSurfaceKHR surface{VK_NULL_HANDLE};
		
		// Devices
		VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
		VkDevice device{VK_NULL_HANDLE};

		//queue family
		uint32_t gfxQueueFamIdx{UINT32_MAX};
		VkQueue gfxQueue{VK_NULL_HANDLE};

		VmaAllocator vmaAllocator{nullptr};

		//swapchain
		VkSwapchainKHR swapchain{VK_NULL_HANDLE};
		std::vector<VkImage> swapchainImages{};
		std::vector<VkImageView> swapchainImageViews{};
		std::vector<VkSemaphore> renderCompleteSemaphores{};
		bool requireSwapchainRecreate{false};
		uint32_t swapchainWidth{};
		uint32_t swapchainHeight{};

		// Image
		VkImage depthImage{VK_NULL_HANDLE};
		VkImageView  depthImageView{VK_NULL_HANDLE};
		VmaAllocation depthImageAllocation{VK_NULL_HANDLE};


		//shader
		VkShaderModule vertShader{VK_NULL_HANDLE};
		VkShaderModule fragShader{VK_NULL_HANDLE};

		// Graphics pipeline
		VkPipelineLayout pipelineLayout{VK_NULL_HANDLE};
		VkPipeline pipeline{VK_NULL_HANDLE};

		// frame and synchronization resources
		VkSemaphore timelineSemaphore {VK_NULL_HANDLE};
		std::array<FrameResources, MaxFramesInFlight> frameResources;

};
