#include "ARBpch.h"
#include "Engine.h"

namespace ARB {

	void Engine::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput();
			appWindow->startUpdate();
			editorCamera->KeyInputProcess(appWindow->mainWindow->window, deltaTime);
			inspector->startUpdate();
			ImGui::Text("Frame Time: %f", deltaTime);

			for (int i = 0; i < renderer->models.size(); i++) {
				if (renderer->shaders.size())
					renderer->models[i]->DrawModel(renderer->shaders[0], editorCamera->GetPerspectiveMatrix(), editorCamera->GetViewMatrix(), glm::translate(glm::mat4(1.0f), glm::vec3(i * 5.0f, -i * 5.0f, -i * 5.0f)), editorCamera->position);
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

	Engine::Engine(Profile* profile, unsigned int width, unsigned int height, char* name) {
		editorLogger = std::make_unique<Editor::Log>("Engine Core");

		editorCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), width, height);

		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name, editorCamera);

		renderer = new ARB::Renderer3D(profile->profileLoc, false);//always after editor window is setup

		appWindow->CreateEditorWindow();
		appWindow->SetEditorWindowCallBacks(true, true, true, true);//Setting Framebuffer size, mouse button, cursor position, mouse scroll callback respectively
		inspector = std::make_shared<Editor::InspectorWindowUI>(appWindow->mainWindow->window, "Inspector", glm::vec2(10, 10), glm::vec2(250, 700));

		renderer->loadAllModelDataToGL();//All the data given to OpenGL on one function here
		renderer->CreateAllShaderPrograms();//All opengl shader program created here

		editorLogger->logger->info("Editor Initialized");
	}

	Engine::~Engine() {
		delete renderer;
	}
}
