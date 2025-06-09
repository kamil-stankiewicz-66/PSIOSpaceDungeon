#include "game/scenes/MainScene.h"
#include "game/core/Asset.h"
#include "game/core/DataBlock.h"
#include "game/ui/BasicButtons.h"
#include "game/core/Game.h"

void MainScene::loadObjects()
{
    //main panel

    auto panelMain = createObject<UIObject>();

    panelMain->getSpritePtr()->setTexture(Asset::Graphics::PANEL.data());
    panelMain->getSpritePtr()->setColor(sf::Color(7, 13, 22));

    float panelMain_scaleX = (0.9f * getGame()->get_window()->get_displaymode().width) / panelMain->getSpritePtr()->getTextureRect().width;
    float panelMain_scaleY = (0.9f * getGame()->get_window()->get_displaymode().height) / panelMain->getSpritePtr()->getTextureRect().height;

    Vector2 panelMain_size(panelMain_scaleX * panelMain->getSpritePtr()->getTextureRect().width,
                           panelMain_scaleY * panelMain->getSpritePtr()->getTextureRect().height);

    panelMain->getTransformPtr()->set_scale(Vector2(panelMain_scaleX, panelMain_scaleY));

    Vector2 panelMain_leftDown(panelMain_size * -0.5f);
    Vector2 panelMain_rightTop(panelMain_size * 0.5f);


    //player data panel

    auto panelPlayerData = createObject<UIObject>(10u);

    panelPlayerData->getSpritePtr()->setTexture(Asset::Graphics::PANEL.data());
    panelPlayerData->getSpritePtr()->setColor(sf::Color(16, 21, 30));

    float panelPlayerData_scaleX = (0.15f * getGame()->get_window()->get_displaymode().width) / panelPlayerData->getSpritePtr()->getTextureRect().width;
    float panelPlayerData_scaleY = (0.3f * getGame()->get_window()->get_displaymode().height) / panelPlayerData->getSpritePtr()->getTextureRect().height;

    panelPlayerData->getTransformPtr()->set_scale(Vector2(panelPlayerData_scaleX, panelPlayerData_scaleY));
    panelPlayerData->getTransformPtr()->set_position(panelMain_rightTop - Vector2(0.12f * panelMain_size.x, 0.3f * panelMain_size.y));


    //player data
    {
        Vector2 panelPlayerData_size(panelPlayerData_scaleX * panelPlayerData->getSpritePtr()->getTextureRect().width,
                                     panelPlayerData_scaleY * panelPlayerData->getSpritePtr()->getTextureRect().height);

        vector<VText*> texts;
        texts.reserve(4);

        for (int i = 0; i < 4; ++i)
        {
            auto title = createObject<TextObject>(20u, panelPlayerData);
            auto titleText = title->getTextPtr();
            titleText->setFont(Asset::Fonts::LIBERATION_SANS.data());
            titleText->setText("<Player Data>");

            title->getTransformPtr()->add_position(0, (panelPlayerData_size.y * 0.35f) - (i * titleText->getLocalBounds().height) * 2.0f);

            texts.emplace_back(titleText);
        }

        texts[0]->setFillColor(sf::Color(144, 127, 127));

        std::ostringstream os;
        os << "Health: " << PlayerData::getMaxHealth();

        texts[1]->setText(os.str());
        texts[1]->setFillColor(sf::Color::White);

        std::ostringstream os1;
        os1 << "Damage: +" << PlayerData::getDamage();

        texts[2]->setText(os1.str());
        texts[2]->setFillColor(sf::Color::White);

        std::ostringstream os2;
        os2 << "Coins: " << PlayerData::getCoins();

        texts[3]->setText(os2.str());
        texts[3]->setFillColor(sf::Color::Yellow);


        for (int i = 1; i < 4; ++i)
        {
            auto t = texts[i]->getObject()->getTransformPtr();
            t->add_position(Vector2(texts[i]->getLocalBounds().width* +0.5f));
            t->add_position(Vector2(panelPlayerData_size.x * -0.4f));
            t->add_position(Vector2(0.0f, panelPlayerData_size.y * -0.02f));
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
        panelMain_leftDown.y += getGame()->get_window()->get_displaymode().height /10;

        for (int i = 0; i < buttons.size(); ++i)
        {
            buttons[i]->getTransformPtr()->set_position(panelMain_leftDown + Vector2(space*(i+1)));
        }
    }
}
