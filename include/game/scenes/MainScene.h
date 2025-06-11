#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "engine/core/Scene.h"

///
/// \brief The MainScene class.
///

class MainScene : public Scene
{
    //tags
    static constexpr std::string_view TAG_HEALTH = "TAG_TEXT_01";
    static constexpr std::string_view TAG_DAMAGE = "TAG_TEXT_02";
    static constexpr std::string_view TAG_COINS = "TAG_TEXT_03";
    static constexpr std::string_view TAG_LEVEL = "TAG_TEXT_05";
    static constexpr std::string_view TAG_SLIDER = "SLIDER_01";
    static constexpr std::string_view TAG_EXP = "TAG_TEXT_04";

    //loader
    virtual void loadObjects() override;
};

#endif // MAINSCENE_H
