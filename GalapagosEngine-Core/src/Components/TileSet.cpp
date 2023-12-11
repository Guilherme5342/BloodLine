#include "Galapagos/Components/TileSet.h"

TileSet::TileSet(std::int32_t tileWidth, std::int32_t tileHeight, std::string file) : m_tileSet(m_none, file)
{
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;

    m_tileSet.SetClip(0, 0, m_tileWidth, m_tileHeight);
    m_columns = m_tileSet.GetWidth() / m_tileWidth;
    m_rows = m_tileSet.GetHeight() / m_tileHeight;
}

void TileSet::RenderTile(std::uint32_t index, float x, float y)
{
    if (index >= static_cast<unsigned int>(m_rows * m_columns))
    {
        return;
    }
    std::int32_t xClip = (index % m_columns) * m_tileWidth;
    std::int32_t yClip = (index / m_columns) * m_tileHeight;
    m_tileSet.SetClip(xClip, yClip, m_tileWidth, m_tileHeight);
    m_tileSet.Render(x, y);
}

std::int32_t TileSet::GetTileWidth() const
{
    return m_tileWidth;
}

std::int32_t TileSet::GetTileHeight() const
{
    return m_tileHeight;
}
