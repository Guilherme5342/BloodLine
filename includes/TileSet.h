#pragma once

#include "Sprite.h"
#include "GameObject.h"

class TileSet {

private:
	Sprite tileSet;

	int tileWidth, tileHeight;

	int rows, columns;

public:
	TileSet(GameObject& associated,int tileWidth, int tileHeight, std::string filePath);
	~TileSet();

	void RenderTile(int x, int y, int layerIndex); // Tambem chamado de LayerIndex = Camada Z

	inline int GetTileWidth() {
		return tileWidth;
	}

	inline int GetTileHeight() {
		return tileHeight;
	}


};