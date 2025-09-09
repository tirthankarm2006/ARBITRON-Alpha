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
			void loadGlad();
			void startUpdate();
			Profile* selectedProfile;
			std::vector<Profile*> profiles;
			bool isProfileSelected;
			void displayProfileData(Profile* profile);
		private:
			void InitiateImguiBackend(GLFWwindow* window);
			void ShutdownImguiBackend();
			void CreateNewImguiFrame();
			void RenderAllWindows();
			void setUITheme();
			std::shared_ptr<Editor::Log> profileSelectorLogger;
			EditorWindow* ps_window;
			InspectorWindowUI* inspector;
			void loadProfiles(std::string profilesListLoc);
		};
	}
}

