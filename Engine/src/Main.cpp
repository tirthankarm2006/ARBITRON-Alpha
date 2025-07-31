#include "ARBpch.h"
#include "Engine.h"

int main() {
	ARB::Engine ourApp = ARB::Engine(1280, 720, "Arbitrary Editor");
	ourApp.runEditor();
	return 0;
}