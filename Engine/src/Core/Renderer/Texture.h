#pragma once

#include "EditorLog.h"

namespace ARB {

	typedef struct{
		unsigned char* data;
		int width, height, nrChannels;
		std::string name;
	}TextureData;

	class Texture
	{
	public:
		Texture(std::string& fullPath, bool flip);
		TextureData* getData();
	private:
		TextureData* texture;
		std::unique_ptr<Editor::Log> textureLogger;
	};
}

