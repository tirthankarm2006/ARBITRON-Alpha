#include"ARBpch.h"
#include "EditorWindow.h"

namespace ARB {
	namespace Editor {

		EditorWindow::EditorWindow(unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window") {
			if (glfwInit()) {
				std::cout << "GLFW initiated" << std::endl;
			}
			else
				std::cout << "GLFW could not be initiated" << std::endl;
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			mainWindow->height = height;
			mainWindow->width = width;
			mainWindow->windowName = name;
			mainWindow->window = glfwCreateWindow(width, height, name, NULL, NULL);

			if (mainWindow->window) {
				std::cout << mainWindow->windowName << " window has been created" << std::endl;
			}
			
			glfwMakeContextCurrent(mainWindow->window);

			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cout << "GLAD initiated" << std::endl;
			}
			else
				std::cout << "GLAD could not be initiated" << std::endl;

			glfwSetFramebufferSizeCallback(mainWindow->window, [](GLFWwindow * window, int width, int height)
			{
				glViewport(0, 0, width, height);
			});
			glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		EditorWindow::~EditorWindow() {
		}

		void EditorWindow::processInput(std::shared_ptr<WindowProps> Window) {
			if (glfwGetKey(Window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				closeWindow(Window);
		}

		int EditorWindow::windowShouldClose() {
			return glfwWindowShouldClose(mainWindow->window);
		}

		void EditorWindow::onWindowClosed(std::shared_ptr<WindowProps> Window) {
			glfwDestroyWindow(Window->window);
			std::cout << Window->windowName << " " << "window is destroyed" << std::endl;
			glfwTerminate();
			std::cout << "GLFW Terminated" << std::endl;
		}

		void EditorWindow::closeWindow(std::shared_ptr<WindowProps> Window) {
			glfwSetWindowShouldClose(Window->window, true);
		}

		void EditorWindow::update() {
			glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(mainWindow->window);
			glfwPollEvents();
		}
	}
}