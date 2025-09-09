#include "ARBpch.h"
#include "Model.h"

namespace ARB {
	Model::Model(std::string fullPath, bool useDefaultTex) {
		modelLogger = std::make_unique<Editor::Log>("Engine::Renderer3D::Model");

		Assimp::Importer importer;
		scene = importer.ReadFile(fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		//aiProcess_Triangulate transforms model's primitive shape to a triangle
		//aiProcess_FlipUVs flips the texture coordinates on the y-axis where necessary

		directory = fullPath.substr(0, fullPath.find_last_of('/'));
		modelName = fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.size());

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			modelLogger->logger->error("{}", importer.GetErrorString());
			return;
		}
		else
			modelLogger->logger->info("Model '{}' successfully loaded", modelName);


		processNode(scene->mRootNode);//here the textureDetail textures_loaded are filled

		modelLogger->logger->trace("{0} textures found for 3D Model {1} from directory {2}", textures_Loaded.size(), modelName, directory);

		for (int i = 0; i < textures_Loaded.size(); i++) {
			textures.push_back(new Texture(directory + "/" + textures_Loaded[i].loc_wrt_model, true, useDefaultTex));//If sets default texture then it is for all textures of the model
		}

		//When there is not texture associated to the model in the .obj file
		if (!textures_Loaded.size()) {
			Mesh::TextureDetail texture;
			texture.id = 0;
			texture.type = Mesh::DIFFUSE;
			texture.loc_wrt_model = std::string("data/default_textures/default_texture.png");
			textures_Loaded.push_back((texture));
			for(int k = 0; k < meshes.size(); k++)
			  meshes[k].meshTextures.push_back(texture);

			textures.push_back(new Texture("", true, false));
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

	//TO BE CALLED IN RENDERER3D
	void Model::setUpTextures() {
		for (int i = 0; i < textures_Loaded.size(); i++) {
			unsigned int texID;
			glGenTextures(1, &texID);
			textures_Loaded[i].id = texID;

			glBindTexture(GL_TEXTURE_2D, textures_Loaded[i].id);

			GLenum format;
			if (textures[i]->getNRChanels() == 1)
				format = GL_RED;
			else if (textures[i]->getNRChanels() == 2)
				format = GL_RG;
			else if (textures[i]->getNRChanels() == 3)
				format = GL_RGB;
			else if (textures[i]->getNRChanels() == 4)
				format = GL_RGBA;
			else
				format = GL_RGB;

			glBindTexture(GL_TEXTURE_2D, textures_Loaded[i].id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, textures[i]->getWidth(), textures[i]->getHeight(), 0, format, GL_UNSIGNED_BYTE, textures[i]->getData().data);
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

			glBindTexture(GL_TEXTURE_2D, 0);

			textures[i]->freeData();
			delete textures[i];
		}

		for (int k = 0; k < meshes.size(); k++) {
			for (unsigned int i = 0; i < meshes[k].meshTextures.size(); i++) {
				for (unsigned int j = 0; j < textures_Loaded.size(); j++) {
					if (std::strcmp(textures_Loaded[j].loc_wrt_model.data(), meshes[k].meshTextures[i].loc_wrt_model.data()) == 0) {
						meshes[k].meshTextures[i].id = textures_Loaded[j].id;
						break;
					}
				}
			}
		}
	}

	//TO BE CALLED IN RENDERER3D
	void Model::uploadAllMeshDataToGL() {
		for (int i = 0; i < meshes.size();i++) {
			meshes[i].uploadMeshDataToGL();
		}
	}

	void Model::DrawModel(std::shared_ptr<Shader> shader, glm::mat4& pMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix, glm::vec3 pos) {
		shader->useShader();

		shader->setVec3Uniform("viewPos", pos);
		shader->setMatrix4Uniform("projection", pMatrix);
		shader->setMatrix4Uniform("view", viewMatrix);
		shader->setMatrix4Uniform("model", modelMatrix);

		if (!appliedShaderParams) {
			setShaderValues_3DModel(shader);
			appliedShaderParams = true;
		}
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes[i].drawMesh(shader);
		}
	}

	void Model::setShaderValues_3DModel(std::shared_ptr<Shader> lightingShader) {
		lightingShader->useShader();
		lightingShader->setVec3Uniform("dLight.direction", glm::vec3(1.0f, -1.0f, 1.0f));
		lightingShader->setVec3Uniform("dLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader->setVec3Uniform("dLight.diffuse", glm::vec3(1.5f, 1.5f, 1.5f));
		lightingShader->setVec3Uniform("dLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));
		lightingShader->setFloatUniform("material.shininess", 2.0f);
	}

	void Model::deleteGLData() {
		for (Mesh& mesh : meshes) {
			mesh.deleteBuffer();
			mesh.deleteTextures();
		}
	}
}
