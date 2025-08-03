#include "ARBpch.h"
#include "InspectorWindowUI.h"

namespace ARB {
	namespace Editor {
		void InspectorWindowUI::ui(const char* name) {
			ImGui::Begin(name);
			ImGui::Text("Welcome to Arbitrary Game Engine");
			ImGui::End();
		}

		InspectorWindowUI::InspectorWindowUI(GLFWwindow* window) {
			inspectorLogger = std::make_shared<Editor::Log>("Engine::InspectorWindow");

			//Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;// IF using Docking Branch
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// IF using Docking Branch
			if (ImGui_ImplGlfw_InitForOpenGL(window, true))// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
				inspectorLogger->logger->info("{0} successfully linked to ImGui", glfwGetWindowTitle(window));
			else
				inspectorLogger->logger->error("{0} failed to link to ImGui", glfwGetWindowTitle(window));
			ImGui_ImplOpenGL3_Init();
		}

		void InspectorWindowUI::startUpdate() {

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void InspectorWindowUI::render() {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);

			ImGui::EndFrame();
		}

		void InspectorWindowUI::shutDown() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

		}
	}
}
