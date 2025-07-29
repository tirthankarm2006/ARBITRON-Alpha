#include "ARBpch.h"
#include "InspectorWindowUI.h"

namespace ARB {
	namespace Editor {
		void InspectorWindowUI::ui() {
			ImGui::Begin("Inspector");
			ImGui::Text("Welcome to Arbitrary Game Engine");
			ImGui::End();
		}

		InspectorWindowUI::InspectorWindowUI(GLFWwindow* window) {
			//Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls
			ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
			ImGui_ImplOpenGL3_Init();
		}

		void InspectorWindowUI::startUpdate() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void InspectorWindowUI::endUpdate() {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void InspectorWindowUI::shutDown() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	}
}
