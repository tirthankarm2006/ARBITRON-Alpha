#include "ARBpch.h"
#include "Profile.h"

namespace ARB {
	Profile::Profile(std::string profileLoc) {
		this->profileLoc = profileLoc;
		profileName = profileLoc.substr(profileLoc.find_last_of("/") + 1, profileLoc.size());

		profileLogger->logger->info("Created profile named '{0}' at {1}", profileLoc, profileLoc);

		//Making 'profileName'.arbprofile file
    }
}