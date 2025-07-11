#include "ARBpch.h"
#include "EditorWindow.h"

namespace ARB {
	void EditorWindow::runEditor() {
		while (!editorWindow.windowShouldClose()) {

		}
	}

	EditorWindow::EditorWindow(unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window") {
		editorWindow = ARB::ARBWindow(width, height, name);
	}

	EditorWindow::~EditorWindow() {
		glfwDestroyWindow(ARBWindow::Window->window);
		std::cout << ARBWindow::Window->windowName << " " << "window is closed" << std::endl;
		glfwTerminate();
		std::cout << "GLFW Terminated" << std::endl;
	}
}