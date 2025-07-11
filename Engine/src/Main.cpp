#include "ARBpch.h"
#include "EditorWindow.h"

int main() {
	ARB::EditorWindow editor = ARB::EditorWindow(1280, 720, "Arbitrary Editor Window");
	editor.runEditor();
	return 0;
}