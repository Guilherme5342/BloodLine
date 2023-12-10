#pragma once
#include <string>
#include <vector>
#include <cstdint>

#include "Entity/Component.h"
#include "Entity/GameObject.h"

class TileSet;

class TileMap : public Component
{
public:
    TileMap(GameObject &associated, std::string file, TileSet *tileSet);

    void Load(std::string file);

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