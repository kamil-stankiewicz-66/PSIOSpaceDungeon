#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "engine/component/Component.h"

class LevelManager;

class LevelGenerator : public Component
{
    friend class LevelManager;
    LevelManager* levelManager;

private:
    void generate();
    void generateCorridors();
};

#endif // LEVELGENERATOR_H
