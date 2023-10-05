#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "TileSet.hpp"

#include <iostream>
#include <fstream>

class TileMap : public Component
{

private:
	vector<int> tileMatrix;

	TileSet *tileSet;

	int mapWidth, mapHeight, mapDepth;

public:
	TileMap(GameObject &associated, std::string filePath, TileSet *tileSet);
	~TileMap();

	void Load(std::string filePath);

	void LoadCollisions();

	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

	void SetTileSet(TileSet *tileSet)
	{
		this->tileSet = tileSet;
		associated.box.SetSize(tileSet->GetTileWidth(), tileSet->GetTileHeight());
	}

	/// <summary>
	/// X = Linha
	/// Y = Coluna
	/// Z = Camada
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="depth"></param>
	/// <returns></returns>
	inline int &At(int x, int y, int depth = 0)
	{
		return tileMatrix[x + y * mapWidth + depth * mapWidth * mapHeight];
	}

	// Herdado por meio de Component
	void Update(float dt);
	void Render();

	inline bool Is(std::string type)
	{
		return type == "TileMap";
	}

	inline int GetWidth()
	{
		return mapWidth;
	}

	inline int GetHeight()
	{
		return mapHeight;
	}

	inline int GetDepth()
	{
		return mapDepth;
	}
};