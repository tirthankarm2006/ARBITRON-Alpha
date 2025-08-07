#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "EditorLog.h"

namespace ARB {

	class Model
	{
	public:
		Model(std::string fullPath);
		void DrawModel(Shader& shader);
	private:
		const aiScene* scene;

		std::vector<TextureDetail> textures_Loaded;//Containing certain details like 
		std::vector<Texture> textures;//Actual Data

		std::vector<Mesh> meshes;
		void processNode(aiNode* node);

		std::string directory;

		std::unique_ptr<Editor::Log> modelLogger;

		void upLoadTextureDataToGl(int index);

		bool appliedShaderParams = false;
	};
}

