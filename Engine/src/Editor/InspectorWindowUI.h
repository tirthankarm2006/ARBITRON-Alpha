#pragma once
#include "EditorWindow.h"

namespace ARB {
	namespace Editor {
		class InspectorWindowUI
		{
		public:
			InspectorWindowUI(GLFWwindow* window);
			void startUpdate(GLFWwindow* window);
			void render();
			void shutDown();
			void ui();
		};
	}
}

