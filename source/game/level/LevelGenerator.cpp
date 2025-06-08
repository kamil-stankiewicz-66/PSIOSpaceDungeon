#include "game/level/LevelGenerator.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"
#include "game/entity/BasicEntity.h"
#include "game/level/LevelElements.h"
#include "game/level/LevelManager.h"
#include "game/core/Parameter.h"
#include "game/level/Tilemap.h"
#include <random>

using namespace std;


///
/// LevelGenerator
///


void LevelGenerator::onAwake()
{
    levelManager = getGame()->get_currentScene()->findObject<LevelManager>();

    random_device rd;
    gen = mt19937(rd());

    if (!levelManager) {
        VDebuger::print("<ERROR> LEVEL_GENERATOR :: levelManager = nullptr");
    }
}


///
/// random int number
///

int LevelGenerator::getRndInt(const int& min, const int& max)
{
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}


Entity* LevelGenerator::createEntity(Scene* scene, const EntityData& data, uint renderLayer, Object* parent)
{
    if (!scene) {
        VDebuger::print("<ERROR> WEAPON :: CREATE_WEAPON :: scene is nullptr");
        return nullptr;
    }

    //empty ptr
    Entity* entity = nullptr;

    //create object
    switch (data.type)
    {
    case EntityData::Type::Basic:
        entity = scene->createObject<BasicEntity>(renderLayer, parent);
        break;
    default:
        return nullptr;
        break;
    }

    //init
    if (entity) {
        entity->set(data);
    }

    return entity;
}


///
/// core
///

void LevelGenerator::generate()
{
    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE :: started");

    generateCorridors();
    generateWalls();

    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE :: ended");
}


///
/// corridors
///

void LevelGenerator::generateCorridors()
{
    int roomsNumber = getRndInt(Parameters::get_levelGenerator_roomsNumber_min(), Parameters::get_levelGenerator_roomsNumber_max());


    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE_CORRIDORS :: rand number of rooms:", roomsNumber);


    int x = 0;
    int y = 0;

    generateRoom(x, y);
    for (int _roomNr = 0; _roomNr < roomsNumber; ++_roomNr)
    {
        generateCorridor(x, y);
        generateRoom(x, y);
    }
}


void LevelGenerator::generateCorridor(int& x, int& y)
{
    //rnd corridor direction
    {
        int direction = getRndInt(0, 3);

        if (direction == m_direction) {
            ++direction;
        }
        else if (direction == 0 && m_direction == 2) {
            ++direction;
        }
        else if (direction == 1 && m_direction == 3) {
            ++direction;
        }

        m_direction = direction;
    }


    //rnd corridor length
    int length = getRndInt(Parameters::get_levelGenerator_corridorLength_min(), Parameters::get_levelGenerator_corridorLength_max());


    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE_CORRIDOR :: rand direction:", m_direction, "; rand lenght:", length);


    //add room lenght
    if (m_direction == 0 || m_direction == 1) {
        length += (m_room_size_x * 2);
    }
    else {
        length += (m_room_size_y * 2);
    }


    int _x = x;
    int _y = y;


    //make corridor
    if (m_direction == 0) //right
    {
        while (x <= _x + length)
        {
            for (int w = 0; w < Parameters::get_levelGenerator_corridor_width(); ++w) {
                levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y+w);
            }

            ++x;
        }
    }
    else if (m_direction == 1) //up
    {
        while (y <= _y + length)
        {
            for (int w = 0; w < Parameters::get_levelGenerator_corridor_width(); ++w) {
                levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x+w, y);
            }

            ++y;
        }
    }
    else if (m_direction == 2) //left
    {
        while (x >= _x + length)
        {
            for (int w = 0; w < Parameters::get_levelGenerator_corridor_width(); ++w) {
                levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y+w);
            }

            --x;
        }
    }
    else //down
    {
        while (y >= _y - length)
        {
            for (int w = 0; w < Parameters::get_levelGenerator_corridor_width(); ++w) {
                levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x+w, y);
            }

            --y;
        }
    }
}


///
/// room
///

void LevelGenerator::generateRoom(int& x, int& y)
{
    m_room_size_x = getRndInt(Parameters::get_levelGenerator_roomSize_min(), Parameters::get_levelGenerator_roomSize_max());
    m_room_size_y = getRndInt(Parameters::get_levelGenerator_roomSize_min(), Parameters::get_levelGenerator_roomSize_max());


    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE_ROOM :: room size:", m_room_size_x, m_room_size_y);

    auto chest = getGame()->get_currentScene()->createObject<Chest>(50u);
    chest->set(Asset::Graphics::CHEST_CLOSED, Asset::Graphics::CHEST_OPEN_FULL, Asset::Graphics::CHEST_OPEN_EMPTY);
    chest->getTransformPtr()->set_position((x*32),y*32);

    for (int _x = x - (m_room_size_x/2); _x < x + (m_room_size_x/2); ++_x)
    {
        for (int _y = y - (m_room_size_y/2); _y < y + (m_room_size_y/2); ++_y)
        {
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, _x, _y);
        }
    }
}


void LevelGenerator::generateWalls()
{
    //shortcuts
    auto tilemap = levelManager->tilemap;
    auto fgtilemap = levelManager->fgTilemap;

    //temp
    list<Vector2> _toRemove;

    //generate
    for (auto tile = tilemap->get().begin(); tile != tilemap->get().end(); ++tile)
    {
        if (!tile->second.get()) {
            continue;
        }


        Vector2 tilePos(tile->first.first, tile->first.second);

        Vector2 upPos(tilePos.x, tilePos.y+1);
        Vector2 downPos(tilePos.x, tilePos.y-1);
        Vector2 rightPos(tilePos.x+1, tilePos.y);
        Vector2 leftPos(tilePos.x-1, tilePos.y);

        const Tile* up = tilemap->getTile(upPos.x, upPos.y);
        const Tile* down = tilemap->getTile(downPos.x, downPos.y);
        const Tile* right = tilemap->getTile(rightPos.x, rightPos.y);
        const Tile* left = tilemap->getTile(leftPos.x, leftPos.y);


        //shortcut
        auto walls = Tilemap::tilepallet.wall;


        //generate
        if (!up) //this is top tile
        {
            if (!left) //this is left-top tile
            {
                fgtilemap->setTile(walls[0][0], upPos.x, upPos.y);
                fgtilemap->setTile(walls[0][1], tilePos.x, tilePos.y);
                fgtilemap->setTile(walls[0][2], downPos.x, downPos.y);
            }
            else if (!right) //this is right-top tile
            {
                fgtilemap->setTile(walls[2][0], upPos.x, upPos.y);
                fgtilemap->setTile(walls[2][1], tilePos.x, tilePos.y);
                fgtilemap->setTile(walls[2][2], downPos.x, downPos.y);
            }
            else //this is center-top tile
            {
                fgtilemap->setTile(walls[1][0], upPos.x, upPos.y);
                fgtilemap->setTile(walls[1][1], tilePos.x, tilePos.y);
                fgtilemap->setTile(walls[1][2], downPos.x, downPos.y);
            }

            //add to remove
            _toRemove.emplace_back(tilePos.x,  tilePos.y);
        }
        else if (!down) //this is down tile
        {
            if (!left) //this is left-down tile
            {
                fgtilemap->setTile(walls[0][3], downPos.x, downPos.y);
            }
            else if (!right) //this is right-down tile
            {
                fgtilemap->setTile(walls[2][3], downPos.x, downPos.y);
            }
            else //this is center-down tile
            {
                fgtilemap->setTile(walls[1][3], downPos.x, downPos.y);
            }
        }
    }

    //clear
    for (const auto& v : _toRemove)
    {
        tilemap->removeTile(v.x, v.y);
    }
}
