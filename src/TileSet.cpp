#include "TileSet.hpp"

TileSet::TileSet(GameObject &associated, int tileWidth, int tileHeight, std::string filePath) : tileSet(associated, filePath)
{
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	tileSet.Open(filePath);

	if (!tileSet.IsOpen())
	{
		std::cout << "Erro ao abrir TileSet" << SDL_GetError() << std::endl;
		return;
	}

	tileSet.SetClip(0, 0, tileWidth, tileHeight);

	columns = tileSet.GetWidth() / tileWidth;
	rows = tileSet.GetHeight() / tileHeight;

	associated.AddComponent(&tileSet);
}

TileSet::~TileSet()
{
}

void TileSet::RenderTile(int x, int y, unsigned int layerIndex)
{
	if (layerIndex >= rows * columns)
		return;

	int tileX = (layerIndex % columns) * tileWidth;
	int tileY = (layerIndex / columns) * tileHeight;

	tileSet.SetClip(tileX, tileY, tileWidth, tileHeight);
	tileSet.Render(x, y, tileWidth, tileHeight);
}
