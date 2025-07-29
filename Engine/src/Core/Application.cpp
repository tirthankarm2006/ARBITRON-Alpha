#include "ARBpch.h"
#include "Application.h"

namespace ARB {

	void Application::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput(appWindow->mainWindow);
			appWindow->startUpdate();
			inspector->startUpdate();
			inspector->ui();


			inspector->endUpdate();
			appWindow->endUpdate();
		}
		inspector->shutDown();
		appWindow->onWindowClosed(appWindow->mainWindow);
	}

	Application::Application(unsigned int width, unsigned int height, char* name) {
		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name);
		editorLogger = std::make_shared<Editor::Log>("Engine Core");
		editorLogger->logger->info("Editor Initialized");
		inspector = std::make_shared<Editor::InspectorWindowUI>(appWindow->mainWindow->window);
	}
}
