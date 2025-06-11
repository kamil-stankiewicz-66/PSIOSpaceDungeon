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
    //tags
    static constexpr std::string_view TAG_TITLE = "TEXT_TITLE";
    static constexpr std::string_view TAG_ENEMIES = "TEXT_ENEMIES_01";
    static constexpr std::string_view TAG_COMPLETE = "TEXT_COMPLETE_01";
    static constexpr std::string_view TAG_EXP = "TEXT_EXP_01";
    static constexpr std::string_view TAG_BUTTON = "TEXT_BUTTON";

    //loader
    virtual void loadObjects() override;

    //exit to main menu
    void exit();

    //helper
    uint countExp() const;
};

#endif // PAUSESCENE_H
