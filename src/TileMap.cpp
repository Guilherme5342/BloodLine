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
	ifstream srcFile(filePath.c_str());

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
		string entryString;
		std::getline(srcFile, entryString, comma);

		tileMatrix.push_back(atoi(entryString.c_str()));
	}

	srcFile.close();
}

void TileMap::LoadCollisions()
{
	if (tileMatrix.empty() || tileSet == nullptr)
	{
		cout << "Colisoes nao podem" << endl;
		return;
	}

	for (int i = 0; i < tileMatrix.size(); i++)
	{
		GameObject *tileObj = new GameObject("Tile" + i);
		Collider *tileCollider = new Collider(*tileObj);
		tileObj->AddComponent(tileCollider);

		tileObj->box = Rect();

		Game::Instance().GetState().AddObject(tileObj);
	}
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
			tileSet->RenderTile(i * tileX + (associated.box.x - cameraX), j * tileY + (associated.box.y - cameraY),
								(int)At(i, j, layer));
		}
	}
}

void TileMap::Update(float dt)
{
}

void TileMap::Render()
{
	for (int z = 0; z < mapDepth; z++)
	{
		RenderLayer(z, Camera::GetCurrentCamPos().x * (z + 1), Camera::GetCurrentCamPos().y * (z + 1));
	}
}
