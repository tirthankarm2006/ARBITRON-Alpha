#pragma once

#include"ARBWindow.h"

namespace ARB{
	class EditorWindow : ARBWindow{

	public:
		ARB::ARBWindow editorWindow;
		void runEditor();
		EditorWindow(unsigned int, unsigned int, char*);
		~EditorWindow();
	};
}
