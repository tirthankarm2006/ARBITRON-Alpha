#pragma once
#include "EditorWindow.h"

namespace ARB {
	namespace Editor {
		class InspectorWindowUI
		{
		public:
			InspectorWindowUI(GLFWwindow* window);
			void startUpdate();
			void endUpdate();
			void shutDown();
			void ui();
		};
	}
}

