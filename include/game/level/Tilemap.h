#ifndef TILEMAP_H
#define TILEMAP_H

#include "engine/object/Object.h"

///
/// \brief A single cell in tilemap.
///

class Tile : public VSprite
{
private:
    float exceedability;

public:
    Tile(const float& exceedability = 1.0f);
    const float& getExceedability() const;
};

///
/// \brief The TilePallet class
///

struct TilePallet
{
    shared_ptr<Tile> main = nullptr;

private:
    friend class Tilemap;
    void init();
};

///
/// \brief A class representing a two-dimensional sprite grid.
///

class Tilemap : public GameObject
{
private:
    map<pair<int,int>, shared_ptr<Tile>> tilemap;
    float scale;
    float cellSize;

    virtual void onAwake() override;
    virtual void onUpdate(float) override;
    void render();

public:
    TilePallet tilepallet;
    void setData(const float &cellSize, const float& scale = 1.0f);
    void setTile(shared_ptr<Tile>& tile, const int& x, const int& y);
    void remove(const int& x, const int& y);
    void clear();

    const Tile* getTile(const int& x, const int& y) const;
};

#endif // TILEMAP_H
