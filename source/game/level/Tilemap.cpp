#include "game/level/Tilemap.h"
#include "game/core/Asset.h"
#include <cmath>


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

vtptr2 make_pallet(string_view asset, const float& factor, const int& size_x, const int& size_y)
{
    vtptr2 temp2;

    for (int _x = 0; _x < size_x; ++_x)
    {
        vtptr temp1;

        for (int _y = 0; _y < size_y; ++_y)
        {
            auto tile = make_shared<Tile>(factor);
            tile->setTexture(asset.data());
            tile->setTextureRect(sf::IntRect(_x*16, _y*16, 16, 16));

            temp1.emplace_back(tile);
        }

        temp2.emplace_back(temp1);
    }

    return temp2;
}

void TilePallet::init()
{
    if (isInited) {
        return;
    }

    //bool
    isInited = true;


    //main floor
    floor_main = make_shared<Tile>(1.0f);
    floor_main->setTexture(Asset::Graphics::FLOOR_MAIN.data());

    //wall
    wall = make_pallet(Asset::Graphics::WALL_MAIN, 0.0f, 3, 4);

    //light floor
    floor_light_main = make_shared<Tile>(0.25f);
    floor_light_main->setTexture(Asset::Graphics::FLOOR_LIGHT.data());
    floor_light_main->setTextureRect(sf::IntRect(4*16, 0, 16, 16));
    floor_light = make_pallet(Asset::Graphics::FLOOR_LIGHT, 0.25f, 4, 3);

    //empty
    empty = make_shared<Tile>(0.0f);
    empty->setTexture(Asset::Graphics::EMPTY.data());
}


///
/// Tilemap
///

TilePallet Tilemap::tilepallet;

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

    for (auto it = tilemap.begin(); it != tilemap.end(); ++it)
    {
        if (auto& tile = it->second) {
            tile->render(getGame(), tile2realPos(it->first.first, it->first.second), _scaleVec, 0.0f, false, false);
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

void Tilemap::removeTile(const int& x, const int& y) {
    tilemap.erase(make_pair(x, y));
}

void Tilemap::clear() {
    tilemap.clear();
}


const map<pair<int,int>, tptr>& Tilemap::get() const {
    return tilemap;
}

const Tile* Tilemap::getTile(const int& x, const int& y) const
{
    auto it = tilemap.find(make_pair(x, y));

    if (it != tilemap.end()) {
        return it->second.get();
    }

    return nullptr;
}

const Tile* Tilemap::getTileRealPos(const float& x, const float& y)
{
    auto _pos = real2tilePos(x, y);
    return getTile(_pos.first, _pos.second);
}


const std::pair<int, int> Tilemap::real2tilePos(const float& x, const float& y)
{
    float scaledCellSize = cellSize * scale;
    return std::make_pair(
        static_cast<int>(std::floor(x / scaledCellSize)),
        static_cast<int>(std::floor(y / scaledCellSize))
        );
}


const Vector2 Tilemap::tile2realPos(const int& x, const int& y)
{
    float scaledCellSize = cellSize * scale;
    return {
        x * scaledCellSize + scaledCellSize / 2.0f,
        y * scaledCellSize + scaledCellSize / 2.0f
    };
}
