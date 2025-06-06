#include "game/player/PlayerEnemyDetector.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"
#include "game/physics/Rycast.h"
#include "game/player/PlayerCore.h"

void PlayerEnemyDetector::onAwake()
{
    //find tilemap
    tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());

    if (!tilemap) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ENEMY_DETECTOR :: tilemap = nullptr");
        return;
    }

    //find player
    playerCore = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!playerCore) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ENEMY_DETECTOR :: playerCore = nullptr");
        return;
    }

    if (!getGame() || !getGame()->get_currentScene()) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ENEMY_DETECTOR :: game or scene = nullptr");
        return;
    }

    //get camera
    camera = getGame()->get_currentScene()->get_mainCamera();

    if (!camera) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ENEMY_DETECTOR :: camera = nullptr");
        return;
    }

    //add to camera
    camera->addChild(this);

    //create collider
    boxCollider = createComponent<BoxCollider>();

    if (!boxCollider) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ENEMY_DETECTOR :: collider = nullptr");
        return;
    }

    //set collider
    boxCollider->set(getGame()->get_window()->get_displaymode().width * camera->get_viewSize(),
                     getGame()->get_window()->get_displaymode().height * camera->get_viewSize());
}

void PlayerEnemyDetector::onStart()
{

}

void PlayerEnemyDetector::onUpdate(float)
{
    //reset
    this->target = nullptr;

    if (!boxCollider || !tilemap) {
        return;
    }

    //get all collisions
    auto& colls = boxCollider->getCollisions();
    float minDist = numeric_limits<float>::max();

    for (auto it = colls.begin(); it != colls.end(); ++it)
    {
        //collider
        auto coll = *it;

        if (!coll) {
            continue;
        }

        //object
        Entity* obj = dynamic_cast<Entity*>(coll->getObject());

        if (!obj) {
            continue;
        }

        if (!obj->checkTag(Tag::ENEMY.data())) {
            continue;
        }

        //transform
        auto t = obj->getTransformPtr();

        if (!t) {
            continue;
        }

        //rycast
        if (Rycast::hit(tilemap, playerCore->getTransformPtr()->get_position(), t->get_position())) {
            continue;
        }

        //distance
        float dist = playerCore->getTransformPtr()->get_position().distanceToLite(t->get_position());

        if (dist < minDist) {
            minDist = dist;
            this->target = obj;
        }
    }
}

Entity* PlayerEnemyDetector::getTarget() const {
    return this->target;
}

