#pragma once
#include <string>
#include <vector>
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>

class TileSet;

class TileMap : public Component
{
public:
    TileMap(GameObject &associated, TileSet* tileSet, std::string file);
    TileMap(GameObject &associated, TileSet* tileSet, const tmx::Map &map);

    void Load(std::string file);
    void Load(const tmx::Map& map);

    void SetTileSet(TileSet *tileSet);
    std::int32_t At(std::int32_t x, std::int32_t y, std::int32_t z = 0) const;

    void Render() const override;
    void RenderLayer(std::int32_t layer, std::int32_t cameraX = 0, std::int32_t cameraY = 0) const;
    std::int32_t GetWidth() const;
    std::int32_t GetHeight() const;
    std::int32_t GetDepth() const;

    void Update(float deltaTime) override;
    bool Is(std::string type) const override;

private:
    std::vector<int> m_tileMatrix;
    TileSet *m_tileSet;
    std::int32_t m_mapWidth;
    std::int32_t m_mapHeight;
    std::int32_t m_mapDepth;
};