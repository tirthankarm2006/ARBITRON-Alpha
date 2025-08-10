#include "ARBpch.h"
#include "Engine.h"
#include "Renderer/Renderer3D.h"

int main() {
	ARB::Engine ourApp = ARB::Engine(1280, 720, "Arbitrary Editor");
	ourApp.runEditor();
	return 0;
}
