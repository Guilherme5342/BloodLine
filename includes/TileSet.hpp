#pragma once

#include "Sprite.hpp"
#include "GameObject.hpp"

class TileSet
{

private:
	Sprite tileSet;

	int tileWidth, tileHeight;

	int rows, columns;

public:
	TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string filePath);
	~TileSet();

	void RenderTile(int x, int y, unsigned int layerIndex); // Tambem chamado de LayerIndex = Camada Z

	inline int GetTileWidth() const
	{
		return tileWidth;
	}

	inline int GetTileHeight() const
	{
		return tileHeight;
	}

	inline int Columns() const {
		return columns;
	}

};