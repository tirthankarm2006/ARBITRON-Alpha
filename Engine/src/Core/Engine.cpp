#include "ARBpch.h"
#include "Engine.h"

namespace ARB {

	void Engine::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput();
			appWindow->startUpdate();
			inspector->startUpdate();
			inspector->ui("Inspector");

			inspector->render();
			appWindow->endUpdate();
		}
		inspector->shutDown();
		appWindow->onWindowClosed();
	}

	Engine::Engine(unsigned int width, unsigned int height, char* name) {
		editorLogger = std::make_shared<Editor::Log>("Engine Core");
		editorLogger->logger->info("Editor Initialized");
		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name);
		inspector = std::make_shared<Editor::InspectorWindowUI>(appWindow->mainWindow->window);
		renderer = std::make_shared<Renderer3D>("data/modelLocs.txt", "data/shaderLocs.txt");
	}
}
