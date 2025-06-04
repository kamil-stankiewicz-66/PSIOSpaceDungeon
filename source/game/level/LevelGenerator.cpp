#include "game/level/LevelGenerator.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"
#include "game/level/LevelManager.h"
#include "game/core/Parameter.h"
#include "game/level/Tilemap.h"
#include <random>

using namespace std;


//randam generator
int getRandomInt(const int& min, const int& max) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}


///
/// LevelGenerator
///

void LevelGenerator::onAwake()
{
    levelManager = getGame()->get_currentScene()->findObject<LevelManager>();

    if (!levelManager) {
        VDebuger::print("<ERROR> LEVEL_GENERATOR :: levelManager = nullptr");
    }
}

void LevelGenerator::generate()
{
    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE :: started");

    generateCorridors();

    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE :: ended");
}

void LevelGenerator::generateCorridors()
{
    int roomsNumber = getRandomInt(Parameters::get_levelGenerator_roomsNumber_min(), Parameters::get_levelGenerator_roomsNumber_max());


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
    int direction = getRandomInt(0, 3);
    int length = getRandomInt(Parameters::get_levelGenerator_corridorLength_min(), Parameters::get_levelGenerator_corridorLength_max());


    //log
    VDebuger::print("LEVEL_GENERATOR :: GENERATE_CORRIDOR :: rand direction:", direction, "; rand lenght:", length);


    int _x = x;
    int _y = y;


    if (direction == 0) //right
    {
        while (x <= _x + length)
        {
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y-1);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y+1);

            ++x;
        }
    }
    else if (direction == 1) //up
    {
        while (y <= _y + length)
        {
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x-1, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x+1, y);

            ++y;
        }
    }
    else if (direction == 2) //left
    {
        while (x >= _x + length)
        {
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y-1);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y+1);

            --x;
        }
    }
    else //down
    {
        while (y >= _y - length)
        {
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x-1, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x, y);
            levelManager->tilemap->setTile(Tilemap::tilepallet.floor_main, x+1, y);

            --y;
        }
    }
}

void LevelGenerator::generateRoom(const int& x, const int& y)
{

}











