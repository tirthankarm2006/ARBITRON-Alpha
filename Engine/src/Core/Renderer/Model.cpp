#include "ARBpch.h"
#include "Model.h"

namespace ARB {
	Model::Model(std::string fullPath) {
		modelLogger = std::make_unique<Editor::Log>("Engine::Renderer3D::Model");

		Assimp::Importer importer;
		scene = importer.ReadFile(fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		//aiProcess_Triangulate transforms model's primitive shape to a triangle
		//aiProcess_FlipUVs flips the texture coordinates on the y-axis where necessary

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			modelLogger->logger->error("{}", importer.GetErrorString());
			return;
		}

		directory = fullPath.substr(0, fullPath.find_last_of('/'));

		processNode(scene->mRootNode);

		for (TextureDetail& tex : textures_Loaded) {
			textures.push_back(Texture(directory + "/" + tex.loc_wrt_model, true));
		}

		modelLogger->logger->info("{0} textures loaded for 3D Model {1} at {2}", textures_Loaded.size(), fullPath.substr(fullPath.find_last_of("/")+1, fullPath.size()));

		//Uploading all textures to OpenGL
		for (int i = 0; i < textures.size(); i++) {
			upLoadTextureDataToGl(i);
			textures[i].freeData();
		}
	}

	void Model::processNode(aiNode* node){
		//process all the node's meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];//mMeshes of the aiNode* node is a pointer to the array of indexes to the array meshes(mMeshes array of type aiMesh) of aiScene* scene
			//i is the indices to the mesh in the node ONLY. mMeshes[i] is the index to the mesh in the mMeshes[] in the scene node
			meshes.push_back(Mesh(mesh, scene, textures_Loaded));//pushes the mesh objects onto the back of the vector of meshes
		}
		//doing the same of the every children of the root(or the node we just passed in the function)
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i]);
		}
	}

	void Model::upLoadTextureDataToGl(int i) {
		glBindTexture(GL_TEXTURE_2D, textures_Loaded[i].id);

		GLenum format;
		if (textures[i].getNRChanels() == 1)
			format = GL_RED;
		else if (textures[i].getNRChanels() == 2)
			format = GL_RG;
		else if (textures[i].getNRChanels() == 3)
			format = GL_RGB;
		else if (textures[i].getNRChanels() == 4)
			format = GL_RGBA;
		else
			format = GL_RGB;

		glBindTexture(GL_TEXTURE_2D, textures_Loaded[i].id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, textures[i].getWidth(), textures[i].getHeight(), 0, format, GL_UNSIGNED_BYTE, textures[i].getData());
		//2nd argument is 0 because we want to set texture for the base level minmap
		//3rd argument tell what type of format we want to store the texture, our image has only rgb values
		//4th and 5th argument gives the width and height of the texture
		//the 7th and 8th argument specifies the format and the datatype of the source image. The image was loaded with rgb values and stored them as chars(bytes)
		//the last argument is the actual data
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Model::DrawModel(Shader& shader) {
		if (!appliedShaderParams) {
			//setLightValuesShader_3DModel(shader);
			appliedShaderParams = true;
		}
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes[i].drawMesh(shader);
		}
	}

	void setLightValuesShader_3DModel(Shader& lightingShader) {
		
	}
}
