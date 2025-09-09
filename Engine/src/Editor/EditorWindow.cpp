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

			/*
			glfwSetKeyCallback(mainWindow->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Camera& c = *(Camera*)glfwGetWindowUserPointer(window);

				c.KeyInputProcess(window);
				});
			*///Not a good idea to set Key input callbacks from camera movement to glfw
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
		}

		void EditorWindow::CreateEditorWindow() {
			mainWindow->window = glfwCreateWindow(mainWindow->width, mainWindow->height, mainWindow->windowName, NULL, NULL);

			if (mainWindow->window) {
				windowLogger->logger->info("{} window has been created", mainWindow->windowName);
			}
			else
				windowLogger->logger->critical("{} window could not be created", mainWindow->windowName);

			glfwMakeContextCurrent(mainWindow->window);

			/*
			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				windowLogger->logger->info("GLAD Initiated");
			}
			else
				windowLogger->logger->critical("GLAD could not be initiated");

			glEnable(GL_DEPTH_TEST);
			*/

			glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		void EditorWindow::SetEditorWindowCallBacks(bool frameBufferSizeC, bool mouseButtonC, bool mouseScrollC, bool cursorPosC) {
			if (frameBufferSizeC) {
				glfwSetFramebufferSizeCallback(mainWindow->window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
				});
			}

			if (mouseButtonC) {
				glfwSetMouseButtonCallback(mainWindow->window, [](GLFWwindow* window, int button, int action, int mods) {
					if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				});
			}

			if(mouseScrollC || cursorPosC)
			   glfwSetWindowUserPointer(mainWindow->window, &camera);

			if (mouseScrollC) {
				glfwSetScrollCallback(mainWindow->window, [](GLFWwindow* window, double xOffset, double yOffset) {
					std::shared_ptr<Camera>& c = *(std::shared_ptr<Camera>*)glfwGetWindowUserPointer(window);

					c->MouseScrollCallback(window, yOffset);
				});
			}

			if (cursorPosC) {
				glfwSetCursorPosCallback(mainWindow->window, [](GLFWwindow* window, double xPos, double yPos) {
					std::shared_ptr<Camera> c = *(std::shared_ptr<Camera>*)glfwGetWindowUserPointer(window);

					c->MouseMoveCallback(window, xPos, yPos);
				});
			}
		}

		void EditorWindow::SetShowEditorWindow(GLFWwindow* window) {
			glfwShowWindow(window);
		}

		void EditorWindow::SetHideEditorWindow(GLFWwindow* window) {
			glfwHideWindow(window);
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
			windowLogger->logger->trace("{} window has been destroyed", mainWindow->windowName);
			glfwTerminate();
			windowLogger->logger->trace("GLFW terminated");
		}

		void EditorWindow::closeWindow() {
			glfwSetWindowShouldClose(mainWindow->window, true);
		}

		void EditorWindow::startUpdate() {

		}

		void EditorWindow::endUpdate() {
			glfwSwapBuffers(mainWindow->window);
			glfwPollEvents();
		}
	}
}