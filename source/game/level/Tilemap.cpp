#include "game/level/Tilemap.h"
#include "game/core/Asset.h"


///
/// Tile
///

Tile::Tile(const float& exceedability) : exceedability(exceedability) {}

const float& Tile::getExceedability() const
{
    return this->exceedability;
}


///
/// TilePallet
///

void TilePallet::init()
{
    main = make_shared<Tile>(1.0f);
    main->setTexture(Asset::Graphics::FLOOR_MAIN.data());
}


///
/// Tilemap
///

void Tilemap::onAwake()
{
    tilemap.clear();
    tilepallet.init();
}

void Tilemap::onUpdate(float)
{
    if (getTransformPtr()) {
        this->render();
    }
}

void Tilemap::render()
{
    Vector2 _scaleVec(scale, scale);
    Vector2 _position;

    for (auto it = tilemap.begin(); it != tilemap.end(); ++it)
    {
        _position.x = getTransformPtr()->get_position().x + it->first.first * cellSize * scale;
        _position.y = getTransformPtr()->get_position().y + it->first.second * cellSize * scale;

        if (auto& tile = it->second) {
            tile->render(getGame(), _position, _scaleVec, 0.0f, false, false);
        }
    }
}

void Tilemap::setData(const float& _cellSize, const float& _scale)
{
    this->cellSize = _cellSize;
    this->scale = _scale;
}

void Tilemap::setTile(shared_ptr<Tile>& tile, const int& x, const int& y) {
    tilemap[make_pair(x, y)] = tile;
}

void Tilemap::remove(const int& x, const int& y) {
    tilemap.erase(make_pair(x, y));
}

void Tilemap::clear() {
    tilemap.clear();
}

const Tile* Tilemap::getTile(const int& x, const int& y) const
{
    auto it = tilemap.find(make_pair(x, y));

    if (it != tilemap.end()) {
        return it->second.get();
    }

    return nullptr;
}
