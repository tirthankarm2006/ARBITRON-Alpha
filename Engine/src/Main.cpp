#include "ARBpch.h"
#include "EditorWindow.h"

int main() {
	ARB::Editor::EditorWindow editor = ARB::Editor::EditorWindow(1280, 720, "Arbitrary Editor");
	editor.runEditor();
	return 0;
}