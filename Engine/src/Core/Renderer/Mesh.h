#pragma once

#include "Shader.h"

namespace ARB {

	class Mesh
	{
	public:
	typedef enum {
		DIFFUSE = 0,
		SPECULAR,
		NORMAL,
		NOISE,
		MUSHGRAVE
	}TextureType;

	typedef struct {
		unsigned int id;
		TextureType type;
		std::string loc_wrt_model;//location wrt it's model
	}TextureDetail;

		Mesh(aiMesh* mesh, const aiScene* modelScene, std::vector<TextureDetail>& textures_Loaded);
		void drawMesh(std::shared_ptr<Shader> shader);
		void deleteBuffer();
		std::vector<TextureDetail> meshTextures;
	private:
		typedef struct {
			glm::vec3 pos;
			glm::vec3 normal;
			glm::vec2 texCoords;
		}Vertex;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		unsigned int VAO, VBO, EBO;

		void loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texType, std::vector<TextureDetail>& textures_Loaded);
		void uploadDataToGL();
	};
}

