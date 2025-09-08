#pragma once

#include "EditorLog.h"
#include "Shader.h"
#include "Model.h"

namespace ARB {
	class Renderer3D
	{
	public:
		Renderer3D(std::string profileLoc, bool useDefaultTex);
		~Renderer3D();
		void loadAllModelDataToGL();
		void CreateAllShaderPrograms();
		void startUpdate();
		void deleteModelDataFromGl(int index);
		void deleteAllModelDatasFromGl();
		void deleteAllShaders();
		void deleteShader(int index);
		std::vector<std::shared_ptr<Model>> models;
		std::vector<std::shared_ptr<Shader>> shaders;
	private:
		std::vector<std::string> modelLoc;
		void load3DModels(std::string& modelsLoc, bool useDefaultTex);
		std::shared_ptr<Editor::Log> rendererLogger;
		void loadShaders(std::string& defaultShadersLoc);

	};
}


