#ifndef ENTITY_H
#define ENTITY_H

#include "engine/object/Object.h"

class Entity : public GameObject
{
    virtual void onAwake() override;
};

#endif // ENTITY_H
