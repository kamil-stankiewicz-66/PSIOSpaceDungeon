#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "engine/core/Scene.h"

class MainScene;

class MainSceneManager : public Object
{
    MainScene* scene;
    virtual void onAwake() override;
    virtual void onUpdate(float) override;
};

class MainScene : public Scene
{
    friend MainSceneManager;

    //tags
    static constexpr std::string_view TAG_HEALTH = "TAG_TEXT_01";
    static constexpr std::string_view TAG_DAMAGE = "TAG_TEXT_02";
    static constexpr std::string_view TAG_COINS = "TAG_TEXT_03";
    static constexpr std::string_view TAG_LEVEL = "TAG_TEXT_05";
    static constexpr std::string_view TAG_SLIDER = "SLIDER_01";
    static constexpr std::string_view TAG_EXP = "TAG_TEXT_04";

    virtual void loadObjects() override;
    void refresh();
};

#endif // MAINSCENE_H
