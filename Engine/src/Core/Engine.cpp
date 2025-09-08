#include "ARBpch.h"
#include "Engine.h"

namespace ARB {

	void Engine::runEditor() {
		while (!appWindow->windowShouldClose()) {
			appWindow->processInput();
			appWindow->startUpdate();
			renderer->startUpdate();
			editorCamera->KeyInputProcess(appWindow->mainWindow->window, deltaTime);
			CreateNewImguiFrame();

			inspector->createFrame();
			ImGui::Text("Frame Time: %f", deltaTime);

			for (int i = 0; i < renderer->models.size(); i++) {
				if (renderer->shaders.size())
					renderer->models[i]->DrawModel(renderer->shaders[0], editorCamera->GetPerspectiveMatrix(), editorCamera->GetViewMatrix(), glm::translate(glm::mat4(1.0f), glm::vec3(i * 5.0f, -i * 5.0f, -i * 5.0f)), editorCamera->position);
			}

			inspector->endFrame();

			sceneHPanel->createFrame();
			sceneHPanel->endFrame();

			terminalWindow->createFrame();
			terminalWindow->endFrame();

			RenderAllWindows();

			appWindow->endUpdate();

			float currentTime = glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = glfwGetTime();
		}

		ShutdownImguiBackend();
		renderer->deleteAllModelDatasFromGl();
		renderer->deleteAllShaders();
		appWindow->onWindowClosed();
	}

	Engine::Engine(Profile* profile, unsigned int width, unsigned int height, char* name) {
		editorLogger = std::make_unique<Editor::Log>("Engine Core");

		renderer = new ARB::Renderer3D(profile->profileLoc, false);

		editorCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), width, height);

		appWindow = std::make_shared<Editor::EditorWindow>(width, height, name, editorCamera);

		appWindow->CreateEditorWindow();
		appWindow->SetEditorWindowCallBacks(true, true, true, true);//Setting Framebuffer size, mouse button, cursor position, mouse scroll callback respectively

		InitiateImguiBackend(appWindow->mainWindow->window);
		inspector = std::make_shared<Editor::InspectorWindowUI>("Inspector", glm::vec2(1340, 10), glm::vec2(250, 830));
		sceneHPanel = std::make_shared<Editor::InspectorWindowUI>("Scene Hierarchy", glm::vec2(10, 10), glm::vec2(250, 530));
		terminalWindow = std::make_shared<Editor::InspectorWindowUI>("Terminal", glm::vec2(10, 550), glm::vec2(1320, 290));

		setUITheme();

		renderer->loadAllModelDataToGL();//All the data given to OpenGL on one function here
		renderer->CreateAllShaderPrograms();//All opengl shader program created here

		editorLogger->logger->info("Editor Initialized");
	}

	void Engine::InitiateImguiBackend(GLFWwindow* window) {
		//Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;// IF using Docking Branch
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// IF using Docking Branch
		if (ImGui_ImplGlfw_InitForOpenGL(window, true))// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
			editorLogger->logger->info("{0} successfully linked to ImGui", glfwGetWindowTitle(window));
		else
			editorLogger->logger->critical("{0} failed to link to ImGui", glfwGetWindowTitle(window));
		ImGui_ImplOpenGL3_Init();
	}

	void Engine::ShutdownImguiBackend() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Engine::CreateNewImguiFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void Engine::RenderAllWindows() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
		ImGui::EndFrame();
	}

	void Engine::setUITheme() {
		auto& colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	Engine::~Engine() {
		delete renderer;
	}
}
