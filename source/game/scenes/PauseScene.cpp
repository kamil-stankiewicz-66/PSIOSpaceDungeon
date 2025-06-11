#include "game/scenes/PauseScene.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"
#include "game/core/DataBlock.h"
#include "game/core/Parameter.h"
#include "game/ui/BasicButtons.h"
#include "game/core/Game.h"


//static info
PauseSceneDataPack::Type PauseSceneDataPack::type;
int PauseSceneDataPack::killedEnemies;
int PauseSceneDataPack::allEnemies;
bool PauseSceneDataPack::isCompleted;


//load scene
void PauseScene::loadObjects()
{
    if (!getGame() || !getGame()->get_window())
    {
        VDebuger::print("<ERROR> PAUSE_SCENE :: LOAD_OBJECTS :: game or window is nullptr");
        return;
    }



    //display
    const sf::VideoMode display = getGame()->get_window()->get_displaymode();




    //main panel

    auto panelMain = createObject<UIObject>(0u);
    auto panelMainSprite = panelMain->getSpritePtr();

    if (!panelMainSprite)
    {
        VDebuger::print("<ERROR> PAUSE_SCENE :: LOAD_OBJECTS :: panelMainSprite is nullptr");
        return;
    }

    panelMainSprite->setTexture(TextureBase::get(Asset::Graphics::PANEL.data()));
    panelMainSprite->setColor(sf::Color(7, 13, 22, 255));

    float panelMain_scaleX = (0.6f * display.width) / panelMainSprite->getTextureRect().width;
    float panelMain_scaleY = (0.6f * display.height) / panelMainSprite->getTextureRect().height;

    Vector2 panelMain_size(panelMain_scaleX * panelMainSprite->getTextureRect().width,
                           panelMain_scaleY * panelMainSprite->getTextureRect().height);

    if (auto t = panelMain->getTransformPtr())
    {
        t->set_scale(Vector2(panelMain_scaleX, panelMain_scaleY));
    }

    Vector2 panelMain_leftDown(panelMain_size * -0.5f);
    Vector2 panelMain_rightTop(panelMain_size * 0.5f);


    //title
    auto textTitle = createObject<TextObject>(10u, panelMain);
    textTitle->addTag(TAG_TITLE.data());

    if (auto text = textTitle->getTextPtr())
    {
        text->setFont(FontBase::get(Asset::Fonts::BANGERS.data()));
        text->setCharacterSize(100);

        switch (PauseSceneDataPack::type) {
        case PauseSceneDataPack::Type::Completed: text->setText("COMPLETED!"); text->setFillColor(sf::Color::Yellow); break;
        case PauseSceneDataPack::Type::Pause: text->setText("PAUSE"); text->setFillColor(sf::Color::White); break;
        case PauseSceneDataPack::Type::Dead: text->setText("DEAD"); text->setFillColor(sf::Color::Red); break;
        default: text->setText("ERROR"); break;
        }
    }

    if (auto t = textTitle->getTransformPtr())
    {
        t->set_position(Vector2(0.f, panelMain_rightTop.y - (panelMain_size.y * 0.1f)));
    }



    //texts

    auto progressPanel = createObject<UIObject>(20u);
    progressPanel->getTransformPtr()->add_position(0.0f, panelMain_size.y * 0.2f);

    vector<TextObject*> texts;
    texts.reserve(4);

    for (int i = 0; i < 4; ++i)
    {
        auto textObj = createObject<TextObject>(20u, progressPanel);
        auto vText = textObj->getTextPtr();

        if (!vText)
        {
            VDebuger::print("<ERROR> PAUSE_SCENE :: LOAD_OBJECTS :: vText is nullptr");
            return;
        }

        vText->setFont(FontBase::get(Asset::Fonts::LIBERATION_SANS.data()));
        vText->setCharacterSize(40u);
        vText->setFillColor(sf::Color(220, 220, 220, 255));

        texts.emplace_back(textObj);
    }


    texts[1]->addTag(TAG_ENEMIES.data());
    texts[3]->addTag(TAG_COMPLETE.data());


    std::string killedEnemiesStr = std::to_string(PauseSceneDataPack::killedEnemies) + "/" +
                                   std::to_string(PauseSceneDataPack::allEnemies);

    std::string isCompletedStr = std::to_string(PauseSceneDataPack::isCompleted) + "/1";



    texts[0]->getTextPtr()->setText("Killed Enemies");
    texts[1]->getTextPtr()->setText(killedEnemiesStr);
    texts[2]->getTextPtr()->setText("Story");
    texts[3]->getTextPtr()->setText(isCompletedStr);


    texts[0]->getTransformPtr()->set_position(panelMain_leftDown.x);
    texts[1]->getTransformPtr()->set_position(panelMain_rightTop.x);
    texts[2]->getTransformPtr()->set_position(panelMain_leftDown.x, -80.f);
    texts[3]->getTransformPtr()->set_position(panelMain_rightTop.x, -80.f);


    for (int i = 0; i < 4; i+=2)
    {
        if (auto t = texts[i]->getTransformPtr())
        {
            t->add_position(Vector2(texts[i]->getTextPtr()->getLocalBounds().width * 0.5f));
            t->add_position(Vector2(panelMain_size.x * 0.025f));
        }
    }

    for (int i = 1; i < 4; i+=2)
    {
        if (auto t = texts[i]->getTransformPtr())
        {
            t->add_position(Vector2(texts[i]->getTextPtr()->getLocalBounds().width * 0.5f));
            t->add_position(Vector2(panelMain_size.x * -0.07f));
        }
    }


    //exp info
    {
        auto textObj = createObject<TextObject>(20u, progressPanel);
        textObj->addTag(TAG_EXP.data());
        auto vText = textObj->getTextPtr();

        if (!vText)
        {
            VDebuger::print("<ERROR> PAUSE_SCENE :: LOAD_OBJECTS :: vText is nullptr");
            return;
        }

        vText->setFont(FontBase::get(Asset::Fonts::LIBERATION_SANS.data()));
        vText->setCharacterSize(40u);
        vText->setFillColor(sf::Color(220, 220, 220, 255));

        textObj->getTransformPtr()->set_position(panelMain_rightTop.x, -160.f);

        vText->setText("exp: +" + std::to_string(countExp()));


        if (auto t = textObj->getTransformPtr())
        {
            t->add_position(Vector2(vText->getLocalBounds().width * -0.5f));
            t->add_position(Vector2(panelMain_size.x * -0.07f));
        }
    }



    //button

    auto button = createObject<MenuButton>(200u);
    if (auto t = button->getTransformPtr())
    {
        t->set_position(panelMain_rightTop.x, panelMain_leftDown.y);
        t->add_position((-0.1f * panelMain_size.x), (0.1f * panelMain_size.y));
        t->set_scale(Vector2(0.5f, 0.6f));
        int w = button->getSpritePtr()->getTextureRect().width;
        int h = button->getSpritePtr()->getTextureRect().height;
        button->set_reactionAreaSize(w * t->get_scale().x, h * t->get_scale().y);
    }

    button->getTextObj()->getTextPtr()->setCharacterSize(30.f);
    button->addTag(TAG_BUTTON.data());

    bool resume = PauseSceneDataPack::type == PauseSceneDataPack::Type::Pause;

    if (button)
    {
        button->dispose();

        if (resume)
        {
            button->setText("Resume");
            button->addListener([this](){
                this->getGame()->changeScene(GAME_SCENE);
            });
        }
        else
        {
            button->setText("Exit");
            button->addListener([this](){
                this->exit();
            });
        }
    }
}

void PauseScene::exit()
{
    PlayerData::setExpPoints(PlayerData::getExpPoints() + countExp());

    if (auto scene = getGame()->get_scene(GAME_SCENE))
    {
        scene->dispose();
    }
    else
    {
        VDebuger::print("<ERROR> PAUSE_SCENE :: scene is nullptr");
    }

    getGame()->changeScene(MAIN_SCENE);
}

uint PauseScene::countExp() const
{
    float expPoints = PauseSceneDataPack::killedEnemies * PauseSceneDataPack::killedEnemies * Parameters::get_exp_perEnemyKill();
    expPoints *= PauseSceneDataPack::isCompleted ? Parameters::get_exp_bonusLevelCompleteMultiplier() : 1.0f;
    return static_cast<uint>(expPoints);
}
