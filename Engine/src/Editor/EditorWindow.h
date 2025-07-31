#pragma once
#include "EditorLog.h"

namespace ARB{
	namespace Editor {
		class EditorWindow {
		private:
			std::shared_ptr<Editor::Log> windowLogger;
		public:
			struct WindowProps {
				GLFWwindow* window;
				unsigned int width, height;
				char* windowName;
			};
			void processInput();
			int windowShouldClose();
			void onWindowClosed();
			void startUpdate();
			void endUpdate();

			std::shared_ptr<WindowProps> mainWindow = std::make_shared<WindowProps>();
			void closeWindow();
			EditorWindow(unsigned int, unsigned int, char*);
			EditorWindow(){}
			~EditorWindow();
		};
	}
}
