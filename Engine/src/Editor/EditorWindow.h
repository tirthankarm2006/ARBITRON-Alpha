#pragma once

namespace ARB{
	namespace Editor {
		class EditorWindow {
		public:
			struct WindowProps {
				GLFWwindow* window;
				unsigned int width, height;
				char* windowName;
			};
			void processInput(std::shared_ptr<WindowProps>);
			int windowShouldClose();
			void onWindowClosed(std::shared_ptr<WindowProps>);
			void startUpdate();
			void EditorWindow::endUpdate();

			std::shared_ptr<WindowProps> mainWindow = std::make_shared<WindowProps>();
			void closeWindow(std::shared_ptr<WindowProps>);
			EditorWindow(unsigned int, unsigned int, char*);
			EditorWindow(){}
			~EditorWindow();
		};
	}
}
