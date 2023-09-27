#include "TextureLoader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

#include "./stb/stb_image.h"
#include <filesystem>
#include "Assets.h"
using namespace std::experimental::filesystem::v1;

using namespace NCL;
using namespace Rendering;

std::map<std::string, TextureLoadFunction> TextureLoader::fileHandlers;
APILoadFunction TextureLoader::apiFunction = nullptr;

bool TextureLoader::LoadTexture(const std::string& filename, char*& outData, int& width, int &height, int &channels, int&flags) {
	if (filename.empty()) {
		return false;
	}
	std::string extension = GetFileExtension(filename);

	auto it = fileHandlers.find(extension);

	std::string realPath = Assets::TEXTUREDIR + filename;

	if (it != fileHandlers.end()) {
		//There's a custom handler function for this, just use that
		return it->second(realPath, outData, width, height, channels, flags);
	}
	//By default, attempt to use stb image to get this texture
	stbi_uc *texData = stbi_load(realPath.c_str(), &width, &height, &channels, 0);

	if (texData) {
		outData = (char*)texData;
		return true;
	}

	return false;
}

void TextureLoader::RegisterTextureLoadFunction(TextureLoadFunction f, const std::string&fileExtension) {
	fileHandlers.insert(std::make_pair(fileExtension, f));
}

std::string TextureLoader::GetFileExtension(const std::string& fileExtension) {
	path p = path(fileExtension);

	path ext = p.extension();

	return ext.string();
}

void TextureLoader::RegisterAPILoadFunction(APILoadFunction f) {
	if (apiFunction) {
		std::cout << __FUNCTION__ << " replacing previously defined API function." << std::endl;
	}
	apiFunction = f;
}

TextureBase* TextureLoader::LoadAPITexture(const std::string&filename) {
	if (apiFunction == nullptr) {
		std::cout << __FUNCTION__ << " no API Function has been defined!" << std::endl;
		return nullptr;
	}
	return apiFunction(filename);
}