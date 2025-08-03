#pragma once
#include "EditorWindow.h"
#include "EditorLog.h"

namespace ARB {
	namespace Editor {
		class InspectorWindowUI
		{
		public:
			InspectorWindowUI(GLFWwindow* window);
			void startUpdate();
			void render();
			void shutDown();
			void ui(const char* name);
		private:
			std::shared_ptr<Editor::Log> inspectorLogger;
		};
	}
}

