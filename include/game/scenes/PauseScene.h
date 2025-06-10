#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "engine/core/Scene.h"


///
/// \brief To transfer information between scenes.
///

struct PauseSceneDataPack
{
    enum class Type { Completed, Dead, Pause };
    static Type type;
    static int killedEnemies;
    static int allEnemies;
    static bool isCompleted;
};


///
/// \brief The pause/finish/dead scene class.
///

class PauseScene : public Scene
{
    virtual void loadObjects() override;
    void exit();

    uint countExp() const;
};

#endif // PAUSESCENE_H
