#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "engine/core/Scene.h"

class PauseScene;


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
/// \brief The PauseSceneManager class
///

class PauseSceneManager : public Object
{
    PauseScene* scene;
    virtual void onAwake() override;
    virtual void onUpdate(float) override;
};


///
/// \brief The pause/finish/dead scene class.
///

class PauseScene : public Scene
{
    friend class PauseSceneManager;

    static constexpr std::string_view TAG_TITLE = "TEXT_TITLE";
    static constexpr std::string_view TAG_ENEMIES = "TEXT_ENEMIES_01";
    static constexpr std::string_view TAG_COMPLETE = "TEXT_COMPLETE_01";
    static constexpr std::string_view TAG_EXP = "TEXT_EXP_01";
    //static constexpr std::string_view TAG_BUTTON_RESUME = "TEXT_BUTTON_01";
    //static constexpr std::string_view TAG_BUTTON_EXIT = "TEXT_BUTTON_02";
    static constexpr std::string_view TAG_BUTTON = "TEXT_BUTTON";

    virtual void loadObjects() override;
    void refresh();
    void exit();

    uint countExp() const;
};

#endif // PAUSESCENE_H
