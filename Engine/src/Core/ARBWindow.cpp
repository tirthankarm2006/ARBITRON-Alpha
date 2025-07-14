#include"ARBpch.h"
#include "ARBWindow.h"

namespace ARB {
	ARBWindow::ARBWindow(unsigned int width = 640, unsigned int height = 480, char* name = "Window") {
		if (glfwInit()) {
			std::cout << "GLFW initiated" << std::endl;
		}
		else
			std::cout << "GLFW could not initiated" << std::endl;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		Window->height = height;
		Window->width = width;
		Window->windowName = name;
		Window->window = glfwCreateWindow(width, height, name, NULL, NULL);

		if (Window->window) {
			std::cout << Window->windowName << " window has been created" << std::endl;
		}

		glfwMakeContextCurrent(Window->window);

		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "GLAD initiated" << std::endl;
		}
		else
			std::cout << "GLAD could not initiated" << std::endl;
	}

	ARBWindow::~ARBWindow() {
		glfwDestroyWindow(Window->window);
		std::cout << Window->windowName << " " << "window is closed" << std::endl;
		glfwTerminate();
		std::cout << "GLFW Terminated" << std::endl;
	}

	int ARBWindow::windowShouldClose() {
		return glfwWindowShouldClose(Window->window);
	}
}
