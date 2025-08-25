#pragma once
#include "EditorWindow.h"
#include "EditorLog.h"
#include "ARB_ProfilingSystem/Profile.h"

namespace ARB {
	namespace Editor {
		class InspectorWindowUI
		{
		public:
			InspectorWindowUI(GLFWwindow* window, const char* name, glm::vec2 pos, glm::vec2 size);
			void startUpdate();
			void render();
			void shutDown();
			void InspectorWindowUI::setUITheme();
		private:
			std::shared_ptr<Editor::Log> inspectorLogger;
			std::string name;
			bool setWindowParams = false;
			glm::vec2 position;
			glm::vec2 size;
		};
	}
}

