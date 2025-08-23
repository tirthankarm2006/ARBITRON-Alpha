#pragma once
#include "ARBpch.h"
#include "EditorWindow.h"
#include "EditorLog.h"
#include "InspectorWindowUI.h"
#include "Renderer/Renderer3D.h"
#include "Camera.h"
#include "ARB_ProfilingSystem/Profile.h"

namespace ARB {
	class Engine
	{
	private:
		std::unique_ptr<Editor::Log> editorLogger;
		std::shared_ptr<Editor::EditorWindow> appWindow;
		std::shared_ptr<Editor::InspectorWindowUI> inspector;
		ARB::Renderer3D* renderer;
		std::shared_ptr<Camera> editorCamera;
	public:
		Engine(Profile* profile, unsigned int width = 1280, unsigned int height = 720, char* name = "Editor Window");
		~Engine();
		void runEditor();
		float deltaTime;
		float lastTime;
	};
}