#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine/component/Component.h"

class LevelGenerator;

class LevelManager : public Component
{
private:
    LevelGenerator* levelGenerator;
};

#endif // LEVELMANAGER_H
