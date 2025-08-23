#pragma once
#include"ARBpch.h"
namespace ARB {

	class ARBWindow {
	protected:
		struct WindowProps {
			GLFWwindow* window;
			unsigned int width, height;
			char* windowName;
	};
	public:
		std::shared_ptr<WindowProps> Window = std::make_shared<WindowProps>();
		ARBWindow(){}
		ARBWindow(unsigned int, unsigned int, char*);
		virtual ~ARBWindow();
		int windowShouldClose();
	};
}

