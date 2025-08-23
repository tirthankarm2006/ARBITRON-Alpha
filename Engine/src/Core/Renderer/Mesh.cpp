#include "ARBpch.h"
#include "Mesh.h"

namespace ARB {
	Mesh::Mesh(aiMesh* mesh, const aiScene* modelScene, std::vector<TextureDetail>& textures_Loaded) {
		//extracting data for the vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;

			vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);//Vertex position
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);//Normal
			if (mesh->mTextureCoords[0]){
				vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);//Texture Coordinates
			}
			else
				vertex.texCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		//extracting data for the indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);//indices are for vertices in one mesh
			}
		}

		//extracting material for a mesh
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = modelScene->mMaterials[mesh->mMaterialIndex];//a mesh has only one material, mesh->mMaterialIndex gives the index of the this mesh's material in the scenes mMaterials array

			//extracting the diffuse textures
			loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE, textures_Loaded);

			//extracting the specular textures
			loadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR, textures_Loaded);
		}

		uploadDataToGL();
	}

	void Mesh::drawMesh(std::shared_ptr<Shader> shader) {
		unsigned int diffuseNr = 0;
		unsigned int specularNr = 0;
		glBindVertexArray(VAO);
		shader->useShader();
		for (unsigned int i = 0; i < meshTextures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);//activating the right texture
			std::string number;
			std::string name;
			if (meshTextures[i].type == DIFFUSE)
				name = "diffuse";
			else if (meshTextures[i].type == SPECULAR)
				name = "specular";

			if (name == "diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "specular")
				number = std::to_string(specularNr++);

			shader->setIntUniform(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, meshTextures[i].id);
		}
		//draw the mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//works with only the texture path not with the data
	void Mesh::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType texType, std::vector<TextureDetail>& textures_loaded) {
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i, &str);//here we get location of the texture file(.jpg) with respect the directory where the model is stored, here "directory"
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++) {
				if (std::strcmp(textures_loaded[j].loc_wrt_model.data(), str.C_Str()) == 0) {
					meshTextures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				TextureDetail texture;
				unsigned int texID;
				glGenTextures(1, &texID);
				texture.id = texID;
				texture.type = texType;
				texture.loc_wrt_model = std::string(str.C_Str());
				textures_loaded.push_back((texture));
				meshTextures.push_back(texture);
			}
		}
	}

	void Mesh::uploadDataToGL() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		//texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Mesh::deleteBuffer() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}