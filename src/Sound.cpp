#include "Sound.hpp"
#include "Resources.hpp"

Sound::Sound(GameObject &associated) : Component(associated)
{
	chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string filePath) : Sound(associated)
{
	Open(filePath);
}

Sound::~Sound()
{
	if (IsOpen() && !IsPlaying())
		Stop();
}

void Sound::Open(std::string filePath)
{
	chunk = Resources::GetSound(filePath);

	if (!chunk)
	{
		std::cout << "Erro ao abrir Som: " << SDL_GetError() << std::endl;
	}
}

void Sound::Play(int times)
{
	channel = Mix_PlayChannel(-1, chunk.get(), times);
	if (channel == -1)
	{
		std::cout << "Som nao tocou: " << SDL_GetError() << std::endl;
	}
}
void Sound::Stop()
{
	Mix_HaltChannel(channel);
}
