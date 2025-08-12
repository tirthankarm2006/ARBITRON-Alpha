#include "ARBpch.h"
#include "Engine.h"

namespace ARB {

	void Engine::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput();
			appWindow->startUpdate();
			inspector->startUpdate();
			inspector->ui("Inspector");
			editorCamera->KeyInputProcess(appWindow->mainWindow->window, deltaTime);

			for (int i = 0; i < renderer->models.size(); i++) {
				if (renderer->models.size() && renderer->shaders.size())
					renderer->models[i]->DrawModel(renderer->shaders[i], editorCamera->GetPerspectiveMatrix(), editorCamera->GetViewMatrix(), glm::translate(glm::mat4(1.0f), glm::vec3(i * 5.0f, -i * 5.0f, -i * 5.0f)), editorCamera->position);
			}

			inspector->render();
			appWindow->endUpdate();

			float currentTime = glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = glfwGetTime();
		}
		inspector->shutDown();

		renderer->deleteAllModelDatasFromGl();
		appWindow->onWindowClosed();
	}

	Engine::Engine(unsigned int width, unsigned int height, char* name) {
		editorLogger = std::make_unique<Editor::Log>("Engine Core");

		editorCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), width, height);
		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name, editorCamera);
		inspector = std::make_shared<Editor::InspectorWindowUI>(appWindow->mainWindow->window);

		renderer = new ARB::Renderer3D("data/modelLocs.txt", "data/shaderLocs.txt", false);//always after editor window is setup

		editorLogger->logger->info("Editor Initialized");
	}

	Engine::~Engine() {
		delete renderer;
	}
}
