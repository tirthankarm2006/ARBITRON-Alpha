#pragma once
#include "ARBpch.h"
#include "EditorWindow.h"
#include "EditorLog.h"
#include "InspectorWindowUI.h"

namespace ARB {
	class Application
	{
	private:
		std::shared_ptr<Editor::Log> editorLogger;
		std::shared_ptr<Editor::EditorWindow> appWindow;
		std::shared_ptr<Editor::InspectorWindowUI> inspector;
	public:
		Application(unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window");
		void runEditor();
	};
}