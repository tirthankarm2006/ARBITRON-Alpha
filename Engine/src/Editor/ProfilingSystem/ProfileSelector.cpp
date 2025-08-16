#include "ARBpch.h"
#include "ProfileSelector.h"

namespace ARB {
	namespace Editor {
		ProfileSelector::ProfileSelector(std::string profileListsLoc) {
			profilerLogger = std::make_shared<Editor::Log>("Engine::Editor::Profiler");

			try {
				std::filesystem::create_directory(profileListsLoc);
			}
			catch (const std::filesystem::filesystem_error& e) {
				profilerLogger->logger->critical("{}", std::string(e.what()));
				return;
			}

			std::fstream readStream;
			readStream.open(profileListsLoc + "/" + "profilesList.txt", std::ios::in);
			if (readStream.is_open()) {
				profilerLogger->logger->info("Opened list of Profiles that has been made");
				std::string line;
				while (std::getline(readStream, line)) {
					profiles.push_back(new Profile(line));
				}
			}
			else {
				readStream.close();
				readStream.open(profileListsLoc + "/" + "profilesList.txt", std::ios::out);
				readStream << "";
				profilerLogger->logger->trace("Created 'profilesList.txt' inside{0} containing list of Profiles", profileListsLoc);
			}
			readStream.close();
		}

		void ProfileSelector::runProfileSelector() {

		}
	}
}