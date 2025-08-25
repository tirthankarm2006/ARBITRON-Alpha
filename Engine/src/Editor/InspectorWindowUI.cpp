#include "ARBpch.h"
#include "InspectorWindowUI.h"

namespace ARB {
	namespace Editor {
		InspectorWindowUI::InspectorWindowUI(GLFWwindow* window, const char* name, glm::vec2 pos, glm::vec2 size) {
			inspectorLogger = std::make_shared<Editor::Log>("Engine::InspectorWindow");
			this->name = name;
			position = pos;
			this->size = size;

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
			ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

			if (!setWindowParams) {
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImVec2 work_pos = viewport->WorkPos; // top-left of work area
				ImVec2 work_size = viewport->WorkSize; // size of work area

				ImGui::SetWindowPos(ImVec2(work_pos.x + position.x, work_pos.y + position.y), ImGuiCond_Always);
				ImGui::SetWindowSize(ImVec2(size.x, size.y));
				setWindowParams = true;
			}
		}

		void InspectorWindowUI::render() {
			ImGui::End();
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

		void InspectorWindowUI::setUITheme() {
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
	}
}
