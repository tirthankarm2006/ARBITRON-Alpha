#include "ARBpch.h"
#include "Application.h"

int main() {
	ARB::Application ourApp = ARB::Application(1280, 720, "Arbitrary Editor");
	ourApp.runEditor();
	return 0;
}