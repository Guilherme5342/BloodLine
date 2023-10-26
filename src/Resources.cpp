#include "Resources.hpp"
#include "Game.hpp"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string filePath)
{
	if (imageTable.find(filePath) != imageTable.end())
	{
		return imageTable[filePath];
	}

	SDL_Texture* texture = IMG_LoadTexture(Game::Instance().GetRenderer(), filePath.c_str());

	// Construtor + Destrutor do Shared Pointer
	imageTable[filePath] = std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture *ptr)
														{ SDL_DestroyTexture(ptr); });

	return imageTable[filePath];
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string filePath)
{
	if (musicTable.find(filePath) != musicTable.end())
	{
		return musicTable[filePath];
	}

	Mix_Music* music = Mix_LoadMUS(filePath.c_str());

	musicTable[filePath] = std::shared_ptr<Mix_Music>(music, [](Mix_Music *mus_Ptr)
													  { Mix_FreeMusic(mus_Ptr); });

	return musicTable[filePath];
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string filePath)
{
	if (soundTable.find(filePath) != soundTable.end())
	{
		return soundTable[filePath];
	}

	Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

	soundTable[filePath] = std::shared_ptr<Mix_Chunk>(chunk, [](Mix_Chunk *s_Ptr)
													  { Mix_FreeChunk(s_Ptr); });

	return soundTable[filePath];
}


std::shared_ptr<TTF_Font> Resources::GetFont(std::string filePath, int fontSize)
{
	if (fontTable.find(filePath) != fontTable.end())
	{
		return fontTable[filePath];
	}

	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);

	fontTable[filePath] = std::shared_ptr<TTF_Font>(font, [](TTF_Font *font_Ptr)
													{ TTF_CloseFont(font_Ptr); });

	return fontTable[filePath];
}

void Resources::ClearImages()
{
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator item;

	for (item = imageTable.begin();  item != imageTable.end(); item++)
	{
		if (!item->second.use_count() != 1)
			continue;

		item = imageTable.erase(item);
	}

}

void Resources::ClearFonts()
{
	std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator item;
	for (item = fontTable.begin(); item != fontTable.end(); item++)
	{
		if (!item->second.use_count() != 1)
			continue;
		cout << "Limpando Fontes" << endl;
		item = fontTable.erase(item);
	}
}

void Resources::ClearMusics()
{
	std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator item;

	for (item = musicTable.begin(); item != musicTable.end(); item++)
	{
		if (!item->second.use_count() != 1)
			continue;

		item = musicTable.erase(item);
	}
}

void Resources::ClearSounds()
{
	std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator item;

	for (item = soundTable.begin(); item != soundTable.end(); item++)
	{
		if (!item->second.use_count() != 1)
			continue;
		item = soundTable.erase(item);
	}
}

void Resources::ClearRemaining()
{
	ClearFonts();
	ClearSounds();
	ClearMusics();
	ClearImages();
}

void Resources::ClearAll()
{
	fontTable.clear();
	soundTable.clear();
	musicTable.clear();
	imageTable.clear();
	
	std::cout << "Tabelas Apagadas" << endl;
}