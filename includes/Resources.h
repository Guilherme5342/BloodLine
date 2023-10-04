#pragma once

#include <cstring>
#include <string.h>
#include <string>

#include <memory>
#include <unordered_map>

#include "SDL_include.h"

#ifdef _WIN32
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

static class Resources
{

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;

public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string filePath);
	static std::shared_ptr<TTF_Font> GetFont(std::string filePath, int fontSize);
	static std::shared_ptr<Mix_Music> GetMusic(std::string filePath);
	static std::shared_ptr<Mix_Chunk> GetSound(std::string filePath);

	static void ClearAll();
};
