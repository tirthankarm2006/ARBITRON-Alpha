#pragma once

#include "EditorLog.h"
#include "Profile.h"
#include "EditorWindow.h"
#include "InspectorWindowUI.h"

namespace ARB {
	namespace Editor {
		class ProfileSelector
		{
		public:
			ProfileSelector(std::string profileDataLoc);
			~ProfileSelector();
			void runProfileSelector();
			Profile* selectedProfile;
			std::vector<Profile*> profiles;
		private:
			std::shared_ptr<Editor::Log> profileSelectorLogger;
			EditorWindow* ps_window;
			InspectorWindowUI* inspector;
			void loadProfiles(std::string profilesListLoc);
			bool isProfileSelected;
		};
	}
}

