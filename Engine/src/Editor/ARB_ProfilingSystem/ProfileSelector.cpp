#include "ARBpch.h"
#include "ProfileSelector.h"

namespace ARB {
	namespace Editor {
		ProfileSelector::ProfileSelector(std::string profileListsLoc) {
			profileSelectorLogger = std::make_shared<Editor::Log>("Engine::Editor::ProfileSelector");

			ps_window = new EditorWindow(1280, 720, "Arbitrary Profile Selector");
			inspector = new InspectorWindowUI(ps_window->mainWindow->window, "Profiles List", glm::vec2(10, 10), glm::vec2(700, 200));
			inspector->setUITheme();
			isProfileSelected = false;
			loadProfiles(profileListsLoc);
		}

		void ProfileSelector::runProfileSelector() {
			while (!ps_window->windowShouldClose()) {
				ps_window->processInput();
				ps_window->startUpdate();
				inspector->startUpdate();

				for (int i = 0; i < profiles.size(); i++) {
					inspector->displayProfileData(profiles[i], isProfileSelected);
					if (isProfileSelected) {
						selectedProfile= profiles[i];
					}
				}

				if (isProfileSelected) {
					profileSelectorLogger->logger->info("Selected profile '{0}' at {1}", selectedProfile->profileName, selectedProfile->profileLoc);
					break;
				}

				inspector->render();
				ps_window->endUpdate();
			}

			inspector->shutDown();
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

		ProfileSelector::~ProfileSelector() {
			delete ps_window;
		}
	}
}