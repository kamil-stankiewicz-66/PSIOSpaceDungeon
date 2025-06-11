#ifndef STORESCENE_H
#define STORESCENE_H

#include "engine/core/Scene.h"

class StoreScene : public Scene
{
protected:
    virtual void loadObjects() override;
    void refresh();
};

#endif // STORESCENE_H

