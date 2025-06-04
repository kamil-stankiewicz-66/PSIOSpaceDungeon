#include "game/scenes/GameScene.h"
#include "game/level/Tilemap.h"
#include "game/player/PlayerCore.h"

void GameScene::loadObjects()
{
    this->set_globalScale(2.0f);

    //player
    {
        createObject<PlayerCore>(50);
    }

    //tilemap
    {
        auto tilemap = createObject<Tilemap>();
        tilemap->setData(16.0f, get_globalScale()*2.0f);

        for (int x = 0; x <2; x++)
        {
            for (int y = 0; y <1; y++)
            {
                tilemap->setTile(tilemap->tilepallet.main, x, y);
            }
        }
        tilemap->setTile(tilemap->tilepallet.main, 0, 1);
    }
}
