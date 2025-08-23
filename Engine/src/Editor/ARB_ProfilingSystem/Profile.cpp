#include "ARBpch.h"
#include "Profile.h"

namespace ARB {
	Profile::Profile(std::string profileLoc) {
		this->profileLoc = profileLoc;
		profileName = profileLoc.substr(profileLoc.find_last_of("/") + 1, profileLoc.size());

		profileLogger = std::make_shared<Editor::Log>("Engine::Editor::Profile");

		profileLogger->logger->info("Created profile named '{0}' at {1}", profileName, profileLoc);

		//Opening or making 'profileName'.arbprofile file

		try {
			std::filesystem::create_directory(profileLoc);
		}
		catch (const std::filesystem::filesystem_error& e) {
			profileLogger->logger->critical("{}", std::string(e.what()));
			return;
		}

		std::fstream readStream;
		readStream.open(profileLoc + "/" + profileName + ".arb_profile", std::ios::out);
		readStream.clear();
		readStream << profileName << std::endl;
		readStream << profileLoc << std::endl;
		readStream.close();
	}
}