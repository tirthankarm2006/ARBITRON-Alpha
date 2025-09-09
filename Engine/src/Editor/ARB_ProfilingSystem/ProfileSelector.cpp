#include "ARBpch.h"
#include "ProfileSelector.h"

namespace ARB {
	namespace Editor {
		ProfileSelector::ProfileSelector(std::string profileListsLoc) {
			profileSelectorLogger = std::make_shared<Editor::Log>("Engine::Editor::ProfileSelector");

			ps_window = new EditorWindow(1280, 720, "Arbitronic Profile Selector");
			ps_window->CreateEditorWindow();
			loadGlad();
			ps_window->SetEditorWindowCallBacks(true, false, false, false);

			InitiateImguiBackend(ps_window->mainWindow->window);
			inspector = new InspectorWindowUI("Profiles List", glm::vec2(10, 10), glm::vec2(700, 200));
			setUITheme();

			isProfileSelected = false;
			selectedProfile = nullptr;
			loadProfiles(profileListsLoc);
		}

		void ProfileSelector::runProfileSelector() {
			while (!ps_window->windowShouldClose()) {
				ps_window->processInput();
				CreateNewImguiFrame();
				inspector->createFrame();
				ps_window->startUpdate();
				startUpdate();

				for (int i = 0; i < profiles.size(); i++) {
					displayProfileData(profiles[i]);
					if (isProfileSelected) {
						selectedProfile = profiles[i];
						break;
					}
				}

				if (isProfileSelected) {
					profileSelectorLogger->logger->info("Selected profile '{0}' at {1}", selectedProfile->profileName, selectedProfile->profileLoc);
					break;
				}

				inspector->endFrame();

				RenderAllWindows();

				ps_window->endUpdate();
			}

			ShutdownImguiBackend();
			ps_window->onWindowClosed();
		}

		void ProfileSelector::loadProfiles(std::string profileListsLoc) {
			try {
				std::filesystem::create_directory(profileListsLoc);
			}
			catch (const std::filesystem::filesystem_error& e) {
				profileSelectorLogger->logger->critical("{}", std::string(e.what()));
				return;
			}

			std::fstream readStream;
			readStream.open(profileListsLoc + "/" + "profilesList.txt", std::ios::in);
			if (readStream.is_open()) {
				profileSelectorLogger->logger->info("Opened list of Profiles that has been made");
				std::string line;
				while (std::getline(readStream, line)) {
					profiles.push_back(new Profile(line));
				}
				profileSelectorLogger->logger->info("{0} Profiles found", profiles.size());
			}
			else {
				readStream.close();
				readStream.open(profileListsLoc + "/" + "profilesList.txt", std::ios::out);
				readStream << "";
				profileSelectorLogger->logger->trace("Created 'profilesList.txt' inside {0} containing list of Profiles", profileListsLoc);
			}
			readStream.close();
		}

		void ProfileSelector::displayProfileData(Profile* profile) {
			ImGui::Text(std::string(profile->profileName).c_str());
			ImGui::Text(std::string("   Location: " + profile->profileLoc).c_str());
			ImGui::SameLine();
			if (ImGui::Button("LOAD")) {
				isProfileSelected = true;
			}
			ImGui::NewLine();
		}

		void ProfileSelector::InitiateImguiBackend(GLFWwindow* window) {
			//Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;// IF using Docking Branch
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// IF using Docking Branch
			if (ImGui_ImplGlfw_InitForOpenGL(window, true))// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
				profileSelectorLogger->logger->info("{0} successfully linked to ImGui", glfwGetWindowTitle(window));
			else
				profileSelectorLogger->logger->critical("{0} failed to link to ImGui", glfwGetWindowTitle(window));
			ImGui_ImplOpenGL3_Init();
		}

		void ProfileSelector::ShutdownImguiBackend() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void ProfileSelector::CreateNewImguiFrame() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void ProfileSelector::RenderAllWindows() {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
			ImGui::EndFrame();
		}

		void ProfileSelector::startUpdate() {
			glClearColor(0.12f, 0.12f, 0.12f, 0.12f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void ProfileSelector::loadGlad() {
			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				profileSelectorLogger->logger->info("GLAD Initiated");
			}
			else
				profileSelectorLogger->logger->critical("GLAD could not be initiated");
			glEnable(GL_DEPTH_TEST);
		}

		void ProfileSelector::setUITheme() {
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

		ProfileSelector::~ProfileSelector() {
			delete ps_window;
		}
	}
}