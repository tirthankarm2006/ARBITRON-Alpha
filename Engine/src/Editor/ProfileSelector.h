#pragma once

#include "EditorLog.h"
#include "Profile.h"

namespace ARB {
	namespace Editor {
		class ProfileSelector
		{
		public:
			ProfileSelector(std::string profileDataLoc);
		private:
			std::shared_ptr<Editor::Log> profilerLogger;
			std::vector<Profile> profiles;
		};
	}
}

