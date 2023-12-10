#include "TileMap.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"

TileMap::TileMap(GameObject &associated, std::string filePath, TileSet *tileSet) : Component(associated)
{
	this->tileSet = tileSet;
	associated.box.SetSize(Vector2(tileSet->GetTileWidth(), tileSet->GetTileHeight()));
	Load(filePath);
}

TileMap::~TileMap()
{
	delete tileSet;
	tileMatrix.clear();
}

void TileMap::Load(std::string filePath)
{
	std::ifstream srcFile(filePath.c_str());

	char comma;

	// De acordo com o arquivo .txt, os primeiros parametros representam especificamente
	// LARGURA, ALTURA, PROFUNDIDADE (Linha 01: 25,25,2)

	srcFile >> mapWidth >> comma;
	srcFile >> mapHeight >> comma;
	srcFile >> mapDepth >> comma;

	//cout << comma << endl;

	tileMatrix.clear();

	for (int i = 0; i < (mapWidth * mapHeight) * mapDepth; i++)
	{
		std::string entryString;
		std::getline(srcFile, entryString, comma);

		tileMatrix.push_back(atoi(entryString.c_str()));
	}

	srcFile.close();
}

void TileMap::LoadCollisions()
{
	if (tileMatrix.empty() || tileSet == nullptr)
	{
		std::cout << "Colisoes nao podem" << std::endl;
		return;
	}
	
	Vector2 size = associated.box.GetCenter() + Vector2(tileSet->GetTileWidth() * GetWidth(),
		tileSet->GetTileHeight() * GetHeight());

	std::cout << size << std::endl;

	Collider* coll = new Collider(associated, size);

	if (associated.GetComponent("Collider") != nullptr)
		associated.RemoveComponent(coll);

	associated.AddComponent(coll);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{

	int tileX = tileSet->GetTileWidth();
	int tileY = tileSet->GetTileHeight();

	// Loop em cada Tile
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{ 
			tileSet->RenderTile(i * tileX + (associated.box.x - cameraX),
				j *  tileY + (associated.box.y - cameraY),
				static_cast<unsigned>(At(i, j, layer)));
		}
	}
}

int TileMap::Hash(std::vector<int>& vector)
{
	int hash;

	for (int i = 0; i < vector.size(); i++)
	{
		int x = vector[i];
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;

		hash ^= x + 0x9e3779b1 + (hash << 6) + (hash >> 2);
	}

	return hash;
}

void TileMap::Update(float dt)
{
}

void TileMap::Render()
{
	for (int z = 0; z < mapDepth; z++)
	{
		RenderLayer(z,
			Camera::GetCurrentCamPos().x * (z + parallaxFactor.x), 
			Camera::GetCurrentCamPos().y * (z + parallaxFactor.y));
	}
}
