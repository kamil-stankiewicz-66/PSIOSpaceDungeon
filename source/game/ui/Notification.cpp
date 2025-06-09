#include "game/ui/Notification.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"


void Notification::onAwake()
{
    VText* text = getTextPtr();

    if (!text) {
        VDebuger::print("<ERROR> NOTIFACATION :: text is nullptr");
        return;
    }

    text->setFont(Asset::Fonts::LIBERATION_SANS.data());
    //text->setCharacterSize(50);
}


void NotificationManager::onUpdate(float dt)
{
    list<Notification*> toDestroy;
    int counter = 0;

    for (auto& notification : this->notifications)
    {
        if (notification->age >= notification->lifeTime) {
            toDestroy.emplace_back(notification);
        }

        notification->getTransformPtr()->set_position(
            getTransformPtr()->get_position() +
            Vector2(-notification->getTextPtr()->getLocalBounds().width,
                    counter * -notification->getTextPtr()->getLocalBounds().height * getGame()->get_currentScene()->get_globalScale())
            );

        ++counter;
        notification->age += dt;
    }

    for (auto& notification : toDestroy)
    {
        getGame()->get_currentScene()->killObject(notification, true);
        this->notifications.remove(notification);
    }
}

void NotificationManager::message(const string& text)
{
    if (!getGame() || !getGame()->get_currentScene()) {
        VDebuger::print("<ERROR> NOTIFICATION_MANAGER :: MESSAGE :: game or scene is nullptr");
        return;
    }

    auto notification = getGame()->get_currentScene()->createObject<Notification>(100000u);
    notification->addTag("notification");

    if (auto vtext = notification->getTextPtr())
    {
        vtext->setText(text);
    }

    this->notifications.emplace_back(notification);
}
