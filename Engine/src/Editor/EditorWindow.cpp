#include"ARBpch.h"
#include "EditorWindow.h"

namespace ARB {
	namespace Editor {

		EditorWindow::EditorWindow(unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window") {
			mainWindow = std::make_shared<WindowProps>();
			windowLogger = std::make_shared<Editor::Log>("Engine::EditorWindow");

			if (glfwInit()) {
				windowLogger->logger->info("GLFW Initiated");
			}
			else
			    windowLogger->logger->error("GLFW could not be initiated");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			mainWindow->height = height;
			mainWindow->width = width;
			mainWindow->windowName = name;
			mainWindow->window = glfwCreateWindow(width, height, name, NULL, NULL);

			if (mainWindow->window) {
				windowLogger->logger->info("{} window has been created", mainWindow->windowName);
			}
			else
				windowLogger->logger->error("{} window could not be created", mainWindow->windowName);
			
			glfwMakeContextCurrent(mainWindow->window);

			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				windowLogger->logger->info("GLAD Initiated");
			}
			else
			    windowLogger->logger->error("GLAD could not be initiated");

			glfwSetFramebufferSizeCallback(mainWindow->window, [](GLFWwindow * window, int width, int height)
			{
				glViewport(0, 0, width, height);
			});
			glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		EditorWindow::~EditorWindow() {
		}

		void EditorWindow::processInput() {
			if (glfwGetKey(mainWindow->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				closeWindow();
		}

		int EditorWindow::windowShouldClose() {
			return glfwWindowShouldClose(mainWindow->window);
		}

		void EditorWindow::onWindowClosed() {
			glfwDestroyWindow(mainWindow->window);
			windowLogger->logger->info("{} window has been destroyed", mainWindow->windowName);
			glfwTerminate();
			windowLogger->logger->info("GLFW terminated");
		}

		void EditorWindow::closeWindow() {
			glfwSetWindowShouldClose(mainWindow->window, true);
		}

		void EditorWindow::startUpdate() {
			glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwPollEvents();
		}

		void EditorWindow::endUpdate() {
			glfwSwapBuffers(mainWindow->window);
		}
	}
}