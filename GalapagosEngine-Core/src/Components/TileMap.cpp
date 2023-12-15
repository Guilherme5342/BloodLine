#include "Galapagos/Components/TileMap.hpp"

#include <fstream>
#include <string>
#include <iostream>

#include "Galapagos/Components/TileSet.hpp"
#include "Galapagos/Core/Camera.hpp"
#include "Galapagos/Components/Collider.hpp"
#include "Galapagos/Core/Game.hpp"

#include "tmxlite/Map.hpp"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated)
{
    m_tileSet = tileSet;
    Load(file);
    m_map.load("res/map/mapa1.tmx");
}

void TileMap::Load(std::string file)
{
    std::ifstream fileStream(file);
    char virgula;

    fileStream >> m_mapWidth >> virgula >> m_mapHeight >> virgula >> m_mapDepth >> virgula;

    std::int32_t value;
    while (fileStream >> value >> virgula)
    {
        m_tileMatrix.push_back(value);
    }
}

void TileMap::LoadCollisions()
{
    if (m_tileMatrix.empty() || m_tileSet == nullptr) {
        return;
    }

    for (size_t i = 0; i < m_tileMatrix.size(); i++)
    {
        int tile = m_tileMatrix[i];
        if (tile == 8) 
        {
            GameObject* colliderObj = new GameObject("TileCollider", 0);
            Collider* tileCollider = new Collider(*colliderObj);
            colliderObj->m_box.SetSize(Vec2(16, 16));
            colliderObj->AddComponent(tileCollider);
            Game::GetCurrentState().AddObject(colliderObj);
        }
    }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    if (m_tileSet)
    {
        delete m_tileSet;
    }
    m_tileSet = tileSet;
}

std::int32_t TileMap::At(std::int32_t x, std::int32_t y, std::int32_t z) const
{
    return m_tileMatrix.at(x + (y * m_mapWidth) + (z * m_mapHeight * m_mapWidth));
}

void TileMap::Render() const
{
    for (std::int32_t layer = 0; layer < m_mapDepth; layer++)
    {
        RenderLayer(layer, Camera::position.x, Camera::position.y);
    }
}

void TileMap::RenderLayer(std::int32_t layer, std::int32_t cameraX, std::int32_t cameraY) const
{
    std::int32_t w = m_tileSet->GetTileWidth();
    std::int32_t h = m_tileSet->GetTileHeight();

    for (std::int32_t x = 0; x < m_mapWidth; x++)
        for (std::int32_t y = 0; y < m_mapHeight; y++)
        {
            m_tileSet->RenderTile(At(x, y, layer), (float)(x * w) - cameraX * (1 + (layer * 0.5)), (float)(y * h) - cameraY * (1 + (layer * 0.5)));
        }
}

std::int32_t TileMap::GetWidth() const
{
    return m_mapWidth;
}

std::int32_t TileMap::GetHeight() const
{
    return m_mapHeight;
}

std::int32_t TileMap::GetDepth() const
{
    return m_mapDepth;
}

void TileMap::Update(float deltaTime)
{
}

bool TileMap::Is(std::string type) const
{
    return type == "TileMap";
}
