#pragma once
#include "EditorLog.h"

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
			void processInput();
			int windowShouldClose();
			void onWindowClosed();
			void startUpdate();
			void endUpdate();

			std::shared_ptr<WindowProps> mainWindow;
			void closeWindow();
			EditorWindow(unsigned int, unsigned int, char*);
			EditorWindow(){}
			~EditorWindow();
		};
	}
}
