#include "ARBpch.h"
#include "Engine.h"
#include "ProfileSelector.h"

int main() {
	ARB::Editor::ProfileSelector profileSelector = ARB::Editor::ProfileSelector("ARB_Profiles");

	ARB::Engine ourApp = ARB::Engine(1280, 720, "Arbitrary Editor");
	ourApp.runEditor();
	return 0;
}
