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
	string uniqueStr = filePath + to_string(fontSize);

	if (fontTable.find(filePath) != fontTable.end())
	{
		return fontTable[filePath];
	}

	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);

	fontTable[uniqueStr] = std::shared_ptr<TTF_Font>(font, [](TTF_Font *font_Ptr)
													{ TTF_CloseFont(font_Ptr); });

	return fontTable[uniqueStr];
}

void Resources::ClearImages()
{
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator item;
	item = imageTable.begin();

	while(item != imageTable.end())
	{
		if ((int)item->second.use_count() == 1)
			item = imageTable.erase(item);
		item++;
	}
}

void Resources::ClearFonts()
{
	std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator item;

	item = fontTable.begin();

	while (item != fontTable.end())
	{
		if ((int)item->second.use_count() == 1)
			item = fontTable.erase(item);
		item++;
	}
}

void Resources::ClearMusics()
{
	std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator item;

	item = musicTable.begin();

	while (item != musicTable.end())
	{
		if ((int)item->second.use_count() == 1) 
			item = musicTable.erase(item);
		item++;
	}
}

void Resources::ClearSounds()
{
	std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator item;

	item = soundTable.begin();

	while (item != soundTable.end())
	{
		if ((int)item->second.use_count() == 1)
			item = soundTable.erase(item);
		item++;;
	}
}

void Resources::ClearRemaining()
{
	ClearImages();
	ClearMusics();
	ClearSounds();
	ClearFonts();
}

void Resources::ClearAll()
{
	imageTable.clear();
	musicTable.clear();
	soundTable.clear();
	fontTable.clear();

	
	std::cout << "Tabelas Apagadas" << endl;
}