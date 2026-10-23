#include <GLFW/glfw3.h>


int main(){
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(1000, 800, "Craft Junction",nullptr, nullptr);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();

	}

	return 0;
}
