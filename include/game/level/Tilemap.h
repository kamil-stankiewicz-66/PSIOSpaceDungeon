#ifndef TILEMAP_H
#define TILEMAP_H

#include "engine/object/Object.h"

class Tile;
using tptr = shared_ptr<Tile>;
using vtptr = vector<tptr>;
using vtptr2 = vector<vtptr>;

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
    //main
    tptr floor_main;

    //wall
    vtptr2 wall;

    //light floor
    tptr floor_light_main;
    vtptr2 floor_light;

private:
    friend class Tilemap;
    bool isInited;
    void init();
};

///
/// \brief A class representing a two-dimensional sprite grid.
///

class Tilemap : public GameObject
{
private:
    map<pair<int,int>, tptr> tilemap;
    float scale;
    float cellSize;

    virtual void onAwake() override;
    virtual void onUpdate(float) override;
    void render();

public:
    static TilePallet tilepallet;
    void setData(const float& cellSize, const float& scale = 1.0f);
    void setTile(shared_ptr<Tile>& tile, const int& x, const int& y);
    void remove(const int& x, const int& y);
    void clear();

    const Tile* getTile(const int& x, const int& y) const;
};

#endif // TILEMAP_H
