#include "ARBpch.h"
#include "Texture.h"

#include "stb/stb_image.h"

namespace ARB {
	Texture::Texture(std::string fullPath, bool flip, bool useDefaultTex) {
		textureLogger = std::make_unique<Editor::Log>("Engine::Renderer3D::Texture");

		std::string name = fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.length());
		texture.name = name;

		stbi_set_flip_vertically_on_load(flip);

        if(useDefaultTex) {
			textureLogger->logger->trace("Did not load texture {0} from {1}, instead loaded default texture", name, fullPath.substr(0, fullPath.find_last_of("/") + 1));
			texture.data = stbi_load("data/default_textures/default_texture1.png", &texture.width, &texture.height, &texture.nrChannels, 0);
			stbi_set_flip_vertically_on_load(!flip);
			return;
		}

		texture.data = stbi_load(fullPath.c_str(), &texture.width, &texture.height, &texture.nrChannels, 0);

		if (texture.data)
			textureLogger->logger->info("Loaded texture {0} from {1}", name, fullPath.substr(0, fullPath.find_last_of("/") + 1));
		else{
			textureLogger->logger->error("Unable to load texture {0} from {1}", name, fullPath.substr(0, fullPath.find_last_of("/") + 1));
			texture.data = stbi_load("data/default_textures/default_texture1.png", &texture.width, &texture.height, &texture.nrChannels, 0);
		}
		stbi_set_flip_vertically_on_load(!flip);
	}

	TextureData Texture::getData() {
		return texture;
	}

	void Texture::freeData() {
		stbi_image_free(texture.data);
	}
}
