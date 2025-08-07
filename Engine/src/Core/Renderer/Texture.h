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
		inline int getNRChanels() { return texture->nrChannels; }
		inline int getWidth() { return texture->width; }
		inline int getHeight() { return texture->height; }
		inline std::string getName() { return texture->name; }
		void freeData();
	private:
		TextureData* texture;
		std::unique_ptr<Editor::Log> textureLogger;
	};
}

