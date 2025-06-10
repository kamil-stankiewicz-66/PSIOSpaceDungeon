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

    vector<uint> weaponIDs = {0, 1, 2};

    float x = 0.f;
    float y = 200.f;

    // ilosc monet
    {
        auto coinsText = createObject<TextObject>(1u);
        auto textPtr = coinsText->getTextPtr();

        if (textPtr)
        {
            textPtr->setFont(Asset::Fonts::LIBERATION_SANS.data());
            textPtr->setCharacterSize(50);
            textPtr->setFillColor(sf::Color::Yellow);

            std::ostringstream os;
            os << "Coins: " << PlayerData::getCoins();
            textPtr->setText(os.str());

            if (auto t = coinsText->getTransformPtr())
                t->set_position(Vector2(-300.f, y + 80.f));
        }
    }


    //Przycisk kupowania
    for (uint id : weaponIDs)
    {
        const WeaponData* data = WeaponSO::get(id);
        if (!data)
        {
            VDebuger::print("<STORE> No data for weapon ID", id);
            continue;
        }

        auto button = createObject<MenuButton>();
        button->setText(data->name + " - " + std::to_string(data->coins) + "c");
        button->getTextObj()->getTextPtr()->setCharacterSize(30.f);

        button->addListener([id, data]() {
            if (PlayerData::getCoins() >= data->coins)
            {
                PlayerData::removeCoins(data->coins);
                VDebuger::print("<STORE> Weapon purchased:", data->name);
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
