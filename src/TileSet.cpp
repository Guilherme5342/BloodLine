#include "TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string filePath) : tileSet(associated,filePath)
{
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	tileSet.Open(filePath);

	if (!tileSet.IsOpen()) {
		cout << "Erro ao abrir TileSet" << SDL_GetError() << endl;
		return;
	}

	rows = tileSet.GetWidth() / tileWidth;
	columns = tileSet.GetHeight() / tileHeight;

	associated.AddComponent(&tileSet);
}

TileSet::~TileSet()
{
}

void TileSet::RenderTile(int x, int y, int layerIndex)
{
	if (layerIndex > rows * columns)
		return;

	int tileX = (layerIndex % columns) * tileWidth;
	int tileY = (layerIndex / columns) * tileHeight;

	tileSet.SetClip(tileX, tileY, tileWidth, tileHeight);
	tileSet.Render(x, y, tileWidth, tileHeight);


}
