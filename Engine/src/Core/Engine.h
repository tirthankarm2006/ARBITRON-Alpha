#pragma once
#include "ARBpch.h"
#include "EditorWindow.h"
#include "EditorLog.h"
#include "InspectorWindowUI.h"
#include "Renderer/Renderer3D.h"

namespace ARB {
	class Engine
	{
	private:
		std::shared_ptr<Editor::Log> editorLogger;
		std::shared_ptr<Editor::EditorWindow> appWindow;
		std::shared_ptr<Editor::InspectorWindowUI> inspector;
		std::shared_ptr<Renderer3D> renderer;
	public:
		Engine(unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window");
		void runEditor();
	};
}