#pragma once
#include "EditorLog.h"
#include "Camera.h"

namespace ARB{
	namespace Editor {
		struct WindowProps {
			GLFWwindow* window;
			unsigned int width, height;
			char* windowName;
		};
		class EditorWindow {
		private:
			std::shared_ptr<Editor::Log> windowLogger;
		public:
			void CreateEditorWindow();
			void processInput();
			int windowShouldClose();
			void onWindowClosed();
			void startUpdate();
			void endUpdate();
			void SetShowEditorWindow(GLFWwindow* window);
			void SetHideEditorWindow(GLFWwindow* window);
			void SetEditorWindowCallBacks(bool frameBufferSizeC, bool mouseButtonC, bool mouseScrollC, bool cursorPosC);

			std::shared_ptr<WindowProps> mainWindow;
			std::shared_ptr<Camera> camera;
			void closeWindow();
			EditorWindow(unsigned int, unsigned int, char*, std::shared_ptr<Camera> cameraPTR);
			EditorWindow(unsigned int, unsigned int, char*);
			EditorWindow(){}
			~EditorWindow();
		};
	}
}
