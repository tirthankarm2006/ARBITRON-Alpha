#include "ARBpch.h"
#include "Engine.h"
#include "ARB_ProfilingSystem/ProfileSelector.h"

int main() {
	ARB::Editor::ProfileSelector profileSelector = ARB::Editor::ProfileSelector("ARB_Profiles");
	profileSelector.runProfileSelector();

	if (!profileSelector.profiles.size())
		return 0;

	ARB::Engine ourApp = ARB::Engine(profileSelector.selectedProfile, 1600, 900, "Arbitrary Editor");
	ourApp.runEditor();

	return 0;
}
