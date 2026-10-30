#include "renderer.hpp"



Renderer::Renderer(){

}

Renderer::~Renderer(){
	cleanUp();
}


void Renderer::cleanUp(){

	if(surface) vkDestroySurfaceKHR(instance, surface,nullptr);

	if(device) vkDestroyDevice(device,nullptr);


	if(instance) vkDestroyInstance(instance,nullptr);

	if(window){
		if(window)glfwDestroyWindow(window);
	}
	glfwTerminate();

}

bool Renderer::initVulkan(){
	if(!createInstance()){
		throw std::runtime_error("Failed to create instance!!!");
	}
	if(!createSurface()){
		throw std::runtime_error("window surface never created");
	}

	if(physicalDevice = findPhysicalDevice(); !physicalDevice){
		throw std::runtime_error("physical Device not created");
	}
	if(!findGraphicQueue()) throw std::runtime_error("couldn't find graphics queue!!!!");

	if(!createDevice(physicalDevice)) throw std::runtime_error("device couldn't be created");

	
	return true;
}



bool Renderer::init(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(1000, 800, "Craft Junction",nullptr, nullptr);

	if(!window){
		throw std::runtime_error("window not created!!!!");
	}
	if(!initVulkan()){
		throw std::runtime_error("Init Vulkan created!!!!");
	}

	return true;
}

void Renderer::run(){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}


}


bool Renderer::createInstance(){
	constexpr VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pApplicationName = "craft junction",
			.apiVersion = VK_API_VERSION_1_4,

	};

	uint32_t glfwExtCount{};
	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);
	std::vector<const char*> requestLayers {
		"VK_LAYER_KHRONOS_validation"

	};
	VkInstanceCreateInfo createInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pApplicationInfo = &appInfo,
			.enabledLayerCount = static_cast<uint32_t>(requestLayers.size()),
			.ppEnabledLayerNames = requestLayers.data(),
			.enabledExtensionCount = glfwExtCount,
			.ppEnabledExtensionNames  = glfwExtensions


	};

	if(vkCreateInstance(&createInfo,nullptr,&instance) != VK_SUCCESS){
		throw std::runtime_error("vulkan Instance not created!!!");

	}
	return  true;
}

bool Renderer::createSurface(){
	if(glfwCreateWindowSurface(instance,window,nullptr,&surface) != VK_SUCCESS){
		throw std::runtime_error("Failed to create window surface!!!!");
	}
	return true;
}

VkPhysicalDevice Renderer::findPhysicalDevice(){
	uint32_t physicalDeviceCount{};
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,nullptr);
	std::vector<VkPhysicalDevice> devices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(instance,&physicalDeviceCount,devices.data());
	VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};

	if(physicalDeviceCount){
		physicalDevice = devices[0];
		
		for(auto &phyDevice: devices){
			VkPhysicalDeviceProperties props{};
			vkGetPhysicalDeviceProperties(phyDevice, &props);
			std::cout << "Physical Device Name:  " << props.deviceName << '\n';
			if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
				physicalDevice = phyDevice;
				break;
			}

		}
	}
	uint32_t formatCount {};
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,nullptr);
	std::vector<VkSurfaceFormatKHR>surfaceFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&formatCount,surfaceFormats.data());

	bool formatSupported{false};
	for(const VkSurfaceFormatKHR &surFormat : surfaceFormats){
		if(surFormat.format == swapchanFormat){
			formatSupported = true;
			break;
		}
	}

	if(!formatSupported){
		throw std::runtime_error("Requested swapchains failed");
		return nullptr;
	}
	return physicalDevice;
}

bool Renderer::findGraphicQueue(){
	uint32_t queueCount{};
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice,&queueCount,nullptr);
	std::vector<VkQueueFamilyProperties2> queueProps(queueCount,{VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2});
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice,&queueCount,queueProps.data());

	for(size_t i{}; i < queueProps.size(); ++i){
		VkBool32 supportPresent{false};
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,i,surface,&supportPresent);
		const auto &props = queueProps[i];

		if(props.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT && supportPresent){
			gfxQueueFamIdx = i;
			return true;
		}


	}
	return false;
}

bool Renderer::createDevice(VkPhysicalDevice physicalDevice){
	float queuePriority{1.f};
	std::vector<uint32_t> queueFamily{gfxQueueFamIdx};

	VkDeviceQueueCreateInfo deviceQueueInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = gfxQueueFamIdx,
			.queueCount = 1,
			.pQueuePriorities = &queuePriority
	};

	VkPhysicalDeviceVulkan14Features supportedFeatures14{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES, .pNext = nullptr   };
	VkPhysicalDeviceVulkan13Features supportedFeatures13{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES, .pNext = &supportedFeatures14   };
	VkPhysicalDeviceVulkan12Features supportedFeatures12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, .pNext = &supportedFeatures13   };
	VkPhysicalDeviceFeatures2 supportedFeatures{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &supportedFeatures12   };
	vkGetPhysicalDeviceFeatures2(physicalDevice, &supportedFeatures);

	// check if what we need is supported
	if (!supportedFeatures13.dynamicRendering || !supportedFeatures13.synchronization2 ||
			!supportedFeatures12.timelineSemaphore)
	{
		throw std::runtime_error("Physical device doesn't meet the feature requirements");
		return false;
	}
	VkPhysicalDeviceVulkan14Features features14
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES,
			.pNext = nullptr,

	};
	VkPhysicalDeviceVulkan13Features features13
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
			.pNext = &features14,
			.synchronization2 = VK_TRUE,
			.dynamicRendering = VK_TRUE,

	};
	VkPhysicalDeviceVulkan12Features features12
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
			.pNext = &features13,
			.timelineSemaphore = VK_TRUE

	};
	VkPhysicalDeviceFeatures2 features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &features12   };
	const std::vector<const char *> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME   };
	VkDeviceCreateInfo devCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = &features,
			.queueCreateInfoCount = 1,
			.pQueueCreateInfos = &deviceQueueInfo,
			.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
			.ppEnabledExtensionNames = deviceExtensions.data(),
			.pEnabledFeatures = nullptr // features struct chain is set in pNext

	};

	if (vkCreateDevice(physicalDevice, &devCreateInfo, nullptr, &device) != VK_SUCCESS)
	{
		throw std::runtime_error("Couldn't create the logical GPU device");
		return false;

	}

	vkGetDeviceQueue(device, gfxQueueFamIdx, 0, &gfxQueue);
	if (!gfxQueue)
	{
		throw std::runtime_error("Couldn't get the graphics queue");

	}




	return true;
}






