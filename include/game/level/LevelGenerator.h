#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "engine/component/Component.h"

class LevelManager;

class LevelGenerator : public Component
{
    friend class LevelManager;
    LevelManager* levelManager;

private:
    virtual void onAwake() override;

    void generate();
    void generateCorridors();
    void generateCorridor(int& x, int& y);
    void generateRoom(const int& x, const int& y);
};

#endif // LEVELGENERATOR_H
