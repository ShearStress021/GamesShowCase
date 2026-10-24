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

	return true;
}






