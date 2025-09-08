#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "EditorLog.h"

namespace ARB {

	class Model
	{
	public:
		Model(std::string fullPath, bool useDefaultTex);
		void DrawModel(std::shared_ptr<Shader> shader, glm::mat4& pMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix, glm::vec3 pos);
		void deleteGLData();
		std::string modelName;
		void uploadAllMeshDataToGL();
		void setUpTextures();
	private:
		const aiScene* scene;

		std::vector<Mesh::TextureDetail> textures_Loaded;//Containing certain details like 
		std::vector<Texture*> textures;//Actual Data

		std::vector<Mesh> meshes;
		void processNode(aiNode* node);

		std::string directory;

		std::unique_ptr<Editor::Log> modelLogger;

		void setShaderValues_3DModel(std::shared_ptr<Shader> shader);

		bool appliedShaderParams = false;
	};
}

