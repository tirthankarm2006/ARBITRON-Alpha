#include "ARBWindow.h"

namespace ARB {
	ARBWindow::ARBWindow(unsigned int width = 640, unsigned int height = 480, char* name = "Window") {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		ARBWindow::Window->height = height;
		ARBWindow::Window->width = width;
		ARBWindow::Window->windowName = name;
		ARBWindow::Window->window = glfwCreateWindow(width, height, name, NULL, NULL);
	}

	ARBWindow::~ARBWindow() {
		
	}

	int ARBWindow::windowShouldClose() {
		return glfwWindowShouldClose(ARBWindow::Window->window);
	}
}
