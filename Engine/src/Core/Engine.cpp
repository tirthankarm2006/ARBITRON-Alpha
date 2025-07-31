#include "ARBpch.h"
#include "Engine.h"

namespace ARB {

	void Engine::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput();
			appWindow->startUpdate();
			inspector->startUpdate(appWindow->mainWindow->window);
			inspector->ui();


			inspector->render();
			appWindow->endUpdate();
		}
		inspector->shutDown();
		appWindow->onWindowClosed();
	}

	Engine::Engine(unsigned int width, unsigned int height, char* name) {
		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name);
		editorLogger = std::make_shared<Editor::Log>("Engine Core");
		editorLogger->logger->info("Editor Initialized");
		inspector = std::make_shared<Editor::InspectorWindowUI>(appWindow->mainWindow->window);
	}
}
