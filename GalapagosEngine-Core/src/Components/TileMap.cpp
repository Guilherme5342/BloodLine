#include "Galapagos/Components/TileMap.h"

#include <fstream>
#include <string>
#include <iostream>

#include "Galapagos/Components/TileSet.h"
#include "Galapagos/Core/Camera.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated)
{
    m_tileSet = tileSet;
    Load(file);
}

void TileMap::Load(std::string file)
{
    std::ifstream fileStream(file);
    char virgula;

    fileStream >> m_mapWidth >> virgula >> m_mapHeight >> virgula >> m_mapDepth >> virgula;

    std::int32_t value;
    while (fileStream >> value >> virgula)
    {
        m_tileMatrix.push_back(value - 1);
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
    return m_tileMatrix.at(x + y * m_mapWidth + z * m_mapHeight * m_mapWidth);
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
