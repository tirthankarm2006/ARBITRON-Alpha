#include"ARBpch.h"
#include "EditorWindow.h"

namespace ARB {
	namespace Editor {

		EditorWindow::EditorWindow(unsigned int width, unsigned int height, char* name, std::shared_ptr<Camera> cameraPTR) {
			mainWindow = std::make_shared<WindowProps>();
			windowLogger = std::make_shared<Editor::Log>("Engine::EditorWindow");
			camera = cameraPTR;

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
			glfwMakeContextCurrent(mainWindow->window);
			glfwHideWindow(mainWindow->window);

			if (mainWindow->window) {
				windowLogger->logger->info("{} window has been created", mainWindow->windowName);
			}
			else
				windowLogger->logger->error("{} window could not be created", mainWindow->windowName);
			
			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				windowLogger->logger->info("GLAD Initiated");
			}
			else
				windowLogger->logger->error("GLAD could not be initiated");

			glEnable(GL_DEPTH_TEST);

			glfwSetFramebufferSizeCallback(mainWindow->window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
				});
			glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			//Specifically for Editor with Camera
			glfwSetMouseButtonCallback(mainWindow->window, [](GLFWwindow* window, int button, int action, int mods) {
				if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			});

			glfwSetWindowUserPointer(mainWindow->window, &camera);//as camera ptr cannot be accessed from lambdas directly

			/*
			glfwSetKeyCallback(mainWindow->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Camera& c = *(Camera*)glfwGetWindowUserPointer(window);

				c.KeyInputProcess(window);
				});
			*///Not a good idea to set Key input callbacks from camera movement to glfw

			glfwSetCursorPosCallback(mainWindow->window, [](GLFWwindow* window, double xPos, double yPos) {
				std::shared_ptr<Camera> c = *(std::shared_ptr<Camera>*)glfwGetWindowUserPointer(window);

				c->MouseMoveCallback(window, xPos, yPos);
				});

			glfwSetScrollCallback(mainWindow->window, [](GLFWwindow* window, double xOffset, double yOffset) {
				std::shared_ptr<Camera>& c = *(std::shared_ptr<Camera>*)glfwGetWindowUserPointer(window);

				c->MouseScrollCallback(window, yOffset);
				});
		}

		EditorWindow::EditorWindow(unsigned int width, unsigned int height, char* name) {
			mainWindow = std::make_shared<WindowProps>();
			windowLogger = std::make_shared<Editor::Log>("Engine::ProfileSelectorWindow");

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
			glfwHideWindow(mainWindow->window);

			if (mainWindow->window) {
				windowLogger->logger->info("{} window has been created", mainWindow->windowName);
			}
			else
				windowLogger->logger->error("{} window could not be created", mainWindow->windowName);

			glfwMakeContextCurrent(mainWindow->window);

			glfwSetFramebufferSizeCallback(mainWindow->window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
				});
			glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				windowLogger->logger->info("GLAD Initiated");
			}
			else
				windowLogger->logger->error("GLAD could not be initiated");

			glEnable(GL_DEPTH_TEST);
		}

		void EditorWindow::SetCurrentEditorWindow(GLFWwindow* window) {
			glfwShowWindow(window);
		}

		EditorWindow::~EditorWindow() {
		}

		void EditorWindow::processInput() {
			
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
			glClearColor(0.15f, 0.15f, 0.15f, 0.15f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void EditorWindow::endUpdate() {
			glfwSwapBuffers(mainWindow->window);
			glfwPollEvents();
		}
	}
}