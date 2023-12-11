#pragma once
#include <string>
#include <cstdint>

#include "Galapagos/Components/Sprite.h"

class TileSet
{
public:
    TileSet(std::int32_t tileWidth, std::int32_t tileHeight, std::string file);

    void RenderTile(std::uint32_t index, float x, float y);

    std::int32_t GetTileWidth() const;
    std::int32_t GetTileHeight() const;

private:
    Sprite m_tileSet;
    GameObject m_none;
    std::int32_t m_rows;
    std::int32_t m_columns;
    std::int32_t m_tileWidth;
    std::int32_t m_tileHeight;
};