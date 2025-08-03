#pragma once

#include "EditorLog.h"
#include "Shader.h"

namespace ARB {
	class Renderer3D
	{
	public:
		Renderer3D(std::string modelsLoc, std::string defaultShadersLoc);
		~Renderer3D();
	private:
		std::vector<std::string> modelLoc;
		std::shared_ptr<Editor::Log> rendererLogger;
		std::vector<Shader> shaders;
	};
}


