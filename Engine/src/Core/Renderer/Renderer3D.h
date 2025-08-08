#pragma once

#include "EditorLog.h"
#include "Shader.h"
#include "Model.h"

namespace ARB {
	class Renderer3D
	{
	public:
		Renderer3D(std::string modelsLoc, std::string defaultShadersLoc);
		~Renderer3D();
		void deleteModelDataFromGl(int index);
		void deleteAllModelDatasFromGl();
	private:
		std::vector<std::string> modelLoc;
		void load3DModels(std::string& modelsLoc);
		std::shared_ptr<Editor::Log> rendererLogger;
		std::vector<std::unique_ptr<Shader>> shaders;
		void loadShaders(std::string& defaultShadersLoc);

		std::vector<Model> models;
	};
}


