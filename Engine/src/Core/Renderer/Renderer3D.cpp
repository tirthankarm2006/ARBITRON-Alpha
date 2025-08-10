#include "ARBpch.h"
#include "Renderer3D.h"

namespace ARB {
	Renderer3D::Renderer3D(std::string modelsLoc, std::string defaultShadersLoc) {
		rendererLogger = std::make_shared<Editor::Log>("Engine::Renderer3D");
		load3DModels(modelsLoc);
		loadShaders(defaultShadersLoc);
	}

	void Renderer3D::load3DModels(std::string& modelsLoc) {
		std::fstream readStream;
		readStream.open(modelsLoc, std::ios::in);
		if (readStream.is_open()) {
			rendererLogger->logger->info("Succesfully opened file containing Model Locations at {}", modelsLoc);
			std::string line;
			int i = 1;
			while (std::getline(readStream, line)) {
				modelLoc.push_back("data/" + line);
				rendererLogger->logger->trace("3D Model {0} at {1}", i++, line);
				models.push_back(std::make_shared<Model>("data/" + line));
			}
		}
		else {
			rendererLogger->logger->error("Could not open file containing Model Locations at {}", modelsLoc);
			rendererLogger->logger->trace("Creating a new file for storing Model Locations");
			readStream.open(modelsLoc, std::ios::out);
			readStream << "\n";
		}
		readStream.close();
	}

	void Renderer3D::loadShaders(std::string& defaultShadersLoc) {
		std::fstream readStream;
		readStream.open(defaultShadersLoc, std::ios::in);
		if (readStream.is_open()) {
			rendererLogger->logger->info("Succesfully Opened file containing Shader Locations at {}", defaultShadersLoc);
			std::string line;

			while (std::getline(readStream, line)) {
				std::string vShader = " ";
				std::string fShader = " ";
				std::string shaderName = " ";
				std::string token = "";

				for (int i = 0; i < line.size(); i++) {
					if (line[i] != ';' && line[i] != '=' && line[i] != ',') {
						token = token + line[i];
					}
					else if (line[i] == '=') {
						shaderName = token;
						token = "";
					}
					else if (line[i] == ',') {
						vShader = token;
						token = "";
					}
					else if (line[i] == ';') {
						fShader = token;
						break;
					}
				}

				shaders.push_back(std::make_shared<Shader>(vShader.c_str(), fShader.c_str(), shaderName));
			}
		}
		else {
			rendererLogger->logger->error("Could not open file containing Shader Locations at {}", defaultShadersLoc);
			rendererLogger->logger->trace("Creating a new file for storing Shader Locations");
			readStream.open(defaultShadersLoc, std::ios::out);
			readStream << "";
		}
		readStream.close();
	}

	void Renderer3D::deleteModelDataFromGl(int index) { 
		models[index]->deleteBuffers(); 
	}

	void Renderer3D::deleteAllModelDatasFromGl() {
		for (std::shared_ptr<Model> model : models)
			model->deleteBuffers();
		rendererLogger->logger->trace("Deleting all Vertex data and Buffer data from OpenGL");
	}

	Renderer3D::~Renderer3D() {

	}
}
