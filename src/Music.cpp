#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string filePath) : Music() {
	Open(filePath);
}

Music::~Music()
{
	Stop(0);
}

void Music::Play(int times)
{
	if (!IsOpen())
		return;

	Mix_PlayMusic(music.get(), times);
}

void Music::Stop(int msToStop) {
	if (!IsOpen())
		return;

	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string filePath) {
	music = Resources::GetMusic(filePath);

	if (!music) {
		std::cout << "Erro ao abrir Musica: " << filePath.c_str() << std::endl;
		std::cout << "Motivo " << SDL_GetError() << std::endl;
	}

}