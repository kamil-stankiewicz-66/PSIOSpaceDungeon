#include "game/scenes/StoreScene.h"
#include "game/ui/BasicButtons.h"
#include "game/core/ScriptableObject.h"
#include "game/entity/Weapon.h"
#include "engine/core/Debuger.h"
#include "game/core/DataBlock.h"
#include "game/core/Asset.h"
#include "engine/core/Engine.h"

//Scena sklepu
void StoreScene::loadObjects()
{

    //vector<uint> weaponIDs = {0, 1, 2};

    float x = 0.f;
    float y = 200.f;

    // ilosc monet
    {
        auto coinsText = createObject<TextObject>(1u);
        auto textPtr = coinsText->getTextPtr();
        coinsText->addTag("coinsTextObj");

        if (textPtr)
        {
            textPtr->setFont(FontBase::get(Asset::Fonts::LIBERATION_SANS.data()));
            textPtr->setCharacterSize(50);
            textPtr->setFillColor(sf::Color::Yellow);

            textPtr->setText("Coins: " + std::to_string(PlayerData::getCoins()));

            if (auto t = coinsText->getTransformPtr())
                t->set_position(Vector2(-300.f, y + 80.f));
        }
    }


    //Przycisk kupowania
    for (const auto& dataPtr : WeaponSO::getAll())
    {
        uint id = dataPtr.first;
        const WeaponData* data = dataPtr.second.get();

        if (!data)
        {
            VDebuger::print("<STORE> No data for weapon ID", id);
            continue;
        }

        auto button = createObject<MenuButton>();
        button->setText(data->name + " - " + std::to_string(data->coins) + "c");
        button->getTextObj()->getTextPtr()->setCharacterSize(30.f);

        button->addListener([id, data, this]() {
            if (PlayerData::getCoins() >= data->coins)
            {
                //buy and use
                if (id != PlayerData::getWeaponID())
                {
                    PlayerData::removeCoins(data->coins);
                    VDebuger::print("<STORE> Weapon purchased:", data->name);

                    //use weapon
                    PlayerData::setWeaponID(id);

                    //refresh
                    this->refresh();
                }
            }
            else
            {
                VDebuger::print("<STORE> Not enough coins!");
            }
        });

        if (auto t = button->getTransformPtr())
        {
            t->set_position(Vector2(x, y));
            y -= 100.f;
        }

    }


    //Przycisk powrotu
    auto back = createObject<MenuButton>();
    back->setText("Back");
    back->addListener([this]() {
        this->getGame()->changeScene("main_scene");

    });

    if (auto t = back->getTransformPtr())
    {
        t->set_position(Vector2(0.f, y - 100.f));
    }
}

void StoreScene::refresh()
{
    VText* text = nullptr;

    if (auto obj = getGame()->get_currentScene()->findObject<TextObject>("coinsTextObj")) {
        text = obj->getTextPtr();
    }

    if (text)
    {
        text->setText("Coins: " + std::to_string(PlayerData::getCoins()));
    }
}
