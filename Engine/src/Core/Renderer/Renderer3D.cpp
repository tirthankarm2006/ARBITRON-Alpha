#include "ARBpch.h"
#include "Renderer3D.h"

namespace ARB {
	Renderer3D::Renderer3D(std::string profileLoc, bool useDefaultTex) {
		rendererLogger = std::make_shared<Editor::Log>("Engine::Renderer3D");
		load3DModels(profileLoc, useDefaultTex);
		loadShaders(profileLoc);
	}

	void Renderer3D::load3DModels(std::string& profileLoc, bool useDefaultTex) {
		std::string modelsLoc = profileLoc + "/" + "data/modelLocs.txt";

		std::fstream readStream;
		readStream.open(modelsLoc, std::ios::in);
		if (readStream.is_open()) {
			rendererLogger->logger->info("Succesfully opened file containing Model Locations at {}", modelsLoc);
			std::string line;
			int i = 1;
			while (std::getline(readStream, line)) {
				if (line[0] == '#')
					continue;
				std::string Model3DLoc = profileLoc + "/" + "data/" + line;
				modelLoc.push_back(Model3DLoc);
				rendererLogger->logger->trace("3D Model {0} at {1}", i++, Model3DLoc);
				rendererLogger->logger->trace("LOADING...");
				models.push_back(std::make_shared<Model>(Model3DLoc, useDefaultTex));
			}
		}
		else {
			rendererLogger->logger->error("Could not open file containing Model Locations at {}", modelsLoc);
			rendererLogger->logger->trace("Creating a new file for storing Model Locations");
			readStream.open(modelsLoc, std::ios::out);
			readStream << "";
		}
		readStream.close();
	}

	void Renderer3D::loadShaders(std::string& profileLoc) {
		std::string defaultShadersLoc = profileLoc + "/" + "data/shaderLocs.txt";

		std::fstream readStream;
		readStream.open(defaultShadersLoc, std::ios::in);
		if (readStream.is_open()) {
			rendererLogger->logger->info("Succesfully Opened file containing Shader Locations at {}", defaultShadersLoc);
			std::string line;

			while (std::getline(readStream, line)) {
				if (line[0] == '#')
					continue;

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

				shaders.push_back(std::make_shared<Shader>((profileLoc + "/" + vShader).c_str(), (profileLoc + "/" + fShader).c_str(), shaderName));
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

	void Renderer3D::startUpdate() {
		glClearColor(0.12f, 0.12f, 0.12f, 0.12f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Renderer3D::loadAllModelDataToGL() {
		for (int i = 0; i < models.size(); i++) {
			models[i]->uploadAllMeshDataToGL();
			models[i]->setUpTextures();
		}
	}

	void Renderer3D::CreateAllShaderPrograms() {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->CreateShaderProgram();
		}
	}

	void Renderer3D::loadGlad() {
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			rendererLogger->logger->info("GLAD Initiated");
		}
		else
			rendererLogger->logger->critical("GLAD could not be initiated");
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer3D::deleteModelDataFromGl(int index) { 
		models[index]->deleteGLData();
	}

	void Renderer3D::deleteAllModelDatasFromGl() {
		for (std::shared_ptr<Model> model : models)
			model->deleteGLData();
		rendererLogger->logger->trace("Deleting all Vertex data and Buffer data from OpenGL");
	}

	void Renderer3D::deleteAllShaders() {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->DeleteShaderProgram();
		}
		rendererLogger->logger->trace("Deleting all Shaders from OpenGL");
	}

	void Renderer3D::deleteShader(int index) {
		shaders[index]->DeleteShaderProgram();
	}

	Renderer3D::~Renderer3D() {

	}
}
