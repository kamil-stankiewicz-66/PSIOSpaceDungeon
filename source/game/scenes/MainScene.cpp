#include "game/scenes/MainScene.h"
#include "game/core/Asset.h"
#include "game/core/DataBlock.h"
#include "game/ui/BasicButtons.h"
#include "game/core/Game.h"
#include "game/ui/Slider.h"

void MainScene::loadObjects()
{
    if (!getGame() || !getGame()->get_window())
    {
        VDebuger::print("<ERROR> MAIN_SCENE :: LOAD_OBJECTS :: game or window is nullptr");
        return;
    }

    const sf::VideoMode& display = getGame()->get_window()->get_displaymode();


    //main panel

    auto panelMain = createObject<UIObject>();
    auto panelMainSprite = panelMain->getSpritePtr();

    if (!panelMainSprite)
    {
        VDebuger::print("<ERROR> MAIN_SCENE :: LOAD_OBJECTS :: panelMainSprite is nullptr");
        return;
    }

    panelMainSprite->setTexture(Asset::Graphics::PANEL.data());
    panelMainSprite->setColor(sf::Color(7, 13, 22));

    float panelMain_scaleX = (0.9f * display.width) / panelMainSprite->getTextureRect().width;
    float panelMain_scaleY = (0.9f * display.height) / panelMainSprite->getTextureRect().height;

    Vector2 panelMain_size(panelMain_scaleX * panelMainSprite->getTextureRect().width,
                           panelMain_scaleY * panelMainSprite->getTextureRect().height);

    if (auto t = panelMain->getTransformPtr())
    {
        t->set_scale(Vector2(panelMain_scaleX, panelMain_scaleY));
    }

    Vector2 panelMain_leftDown(panelMain_size * -0.5f);
    Vector2 panelMain_rightTop(panelMain_size * 0.5f);


    //player data panel
    {
        auto panelPlayerData = createObject<UIObject>(10u);
        auto panelPlayerDataSprite = panelPlayerData->getSpritePtr();

        if (!panelPlayerDataSprite)
        {
            VDebuger::print("<ERROR> MAIN_SCENE :: LOAD_OBJECTS :: panelPlayerDataSprite is nullptr");
            return;
        }

        panelPlayerDataSprite->setTexture(Asset::Graphics::PANEL.data());
        panelPlayerDataSprite->setColor(sf::Color(16, 21, 30));

        float panelPlayerData_scaleX = (0.15f * display.width) / panelPlayerDataSprite->getTextureRect().width;
        float panelPlayerData_scaleY = (0.3f * display.height) / panelPlayerDataSprite->getTextureRect().height;


        if (auto t = panelPlayerData->getTransformPtr())
        {
            t->set_scale(Vector2(panelPlayerData_scaleX, panelPlayerData_scaleY));
            t->set_position(panelMain_rightTop - Vector2(0.12f * panelMain_size.x, 0.3f * panelMain_size.y));
        }
        else
        {
            VDebuger::print("<ERROR> MAIN_SCENE :: LOAD_OBJECTS :: panelPlayerData->getTransformPtr() is nullptr");
            return;
        }


        //player data
        {
            Vector2 panelPlayerData_size(panelPlayerData_scaleX * panelPlayerDataSprite->getTextureRect().width,
                                         panelPlayerData_scaleY * panelPlayerDataSprite->getTextureRect().height);

            vector<VText*> texts;
            texts.reserve(4);

            for (int i = 0; i < 4; ++i)
            {
                auto title = createObject<TextObject>(20u, panelPlayerData);
                auto titleText = title->getTextPtr();

                if (!titleText)
                {
                    VDebuger::print("<ERROR> MAIN_SCENE :: LOAD_OBJECTS :: titleText is nullptr");
                    return;
                }

                titleText->setFont(Asset::Fonts::LIBERATION_SANS.data());
                titleText->setText("<Player Data>");

                title->getTransformPtr()->add_position(0, (panelPlayerData_size.y * 0.35f) - (i * titleText->getLocalBounds().height) * 2.0f);

                texts.emplace_back(titleText);
            }

            texts[0]->setFillColor(sf::Color(144, 127, 127));

            std::ostringstream os_health;
            os_health << "Health: " << PlayerData::getMaxHealth();

            texts[1]->setText(os_health.str());
            texts[1]->setFillColor(sf::Color::White);

            std::ostringstream os_damage;
            os_damage << "Damage: +" << PlayerData::getDamage();

            texts[2]->setText(os_damage.str());
            texts[2]->setFillColor(sf::Color::White);

            std::ostringstream os_coins;
            os_coins << "Coins: " << PlayerData::getCoins();

            texts[3]->setText(os_coins.str());
            texts[3]->setFillColor(sf::Color::Yellow);


            for (int i = 1; i < 4; ++i)
            {
                if (auto t = texts[i]->getObject()->getTransformPtr())
                {
                    t->add_position(Vector2(texts[i]->getLocalBounds().width* +0.5f));
                    t->add_position(Vector2(panelPlayerData_size.x * -0.4f));
                    t->add_position(Vector2(0.0f, panelPlayerData_size.y * -0.02f));
                }
            }
        }
    }


    //level and exp slider
    {
        const float splitFactor = 50.0f;

        auto panelLevel = createObject<UIObject>(10u);

        if (auto t = panelLevel->getTransformPtr())
        {
            t->set_position(panelMain_leftDown.x, panelMain_rightTop.y);
            t->add_position(Vector2(0.35f * panelMain_size.x));
            t->add_position(Vector2(0.0f, -0.3f * panelMain_size.y));
        }


        //text with level info
        auto textLevel = createObject<TextObject>(11u, panelLevel);

        if (auto text = textLevel->getTextPtr())
        {
            text->setFont(Asset::Fonts::BANGERS.data());
            text->setCharacterSize(100);

            std::ostringstream os_playerLevel;
            os_playerLevel << "PLAYER LEVEL: " << PlayerData::getExpLevel();
            text->setText(os_playerLevel.str());
        }

        if (auto t = textLevel->getTransformPtr())
        {
            t->set_position(Vector2(0.f, splitFactor));
        }


        //slider
        auto slider = createObject<Slider>(11u, panelLevel);
        slider->init(true);
        slider->setValueMax(1000.f);
        slider->setValue(PlayerData::getExpPoints());
        slider->setFillColor(sf::Color(220, 245, 0));
        slider->setBackgroundColor(sf::Color(23, 26, 33));
        slider->scaleWidth(1.75f);
        slider->scaleHeight(0.75f);

        if (auto t = slider->getTransformPtr())
        {
            t->set_position(Vector2(0.f, -splitFactor));
        }


        //exp text
        auto textExp = createObject<TextObject>(20u, panelLevel);

        if (auto text = textExp->getTextPtr())
        {
            text->setFont(Asset::Fonts::LIBERATION_SANS.data());
            text->setFillColor(sf::Color(144, 127, 127));

            std::ostringstream os_expPoints;
            os_expPoints << "exp: " << PlayerData::getExpPoints();
            text->setText(os_expPoints.str());

            if (auto t = textExp->getTransformPtr())
            {
                t->set_position(Vector2(-0.5f * slider->getWidth(), -splitFactor * 2.0f));
                t->add_position(Vector2(0.5f * text->getLocalBounds().width));
            }
        }
    }


    //buttons
    {
        auto play_button = createObject<MenuButton>();
        play_button->setText("Play");

        play_button->addListener([this](){
            this->getGame()->changeScene(GAME_SCENE);
        });


        auto store_button = createObject<MenuButton>();
        store_button->setText("Store");

        store_button->addListener([this](){
            this->getGame()->changeScene(STORE_SCENE);
        });


        vector<MenuButton*> buttons {store_button, play_button};
        int space = (panelMain_rightTop.x - panelMain_leftDown.x) / (buttons.size() + 1);
        panelMain_leftDown.y += display.height /10;

        for (int i = 0; i < buttons.size(); ++i)
        {
            if (!buttons[i] || !buttons[i]->getTransformPtr()) {
                continue;
            }

            buttons[i]->getTransformPtr()->set_position(panelMain_leftDown + Vector2(space*(i+1)));
        }
    }
}
