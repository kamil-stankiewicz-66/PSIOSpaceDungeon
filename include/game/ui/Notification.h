#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "engine/object/Object.h"
#include <list>


///
/// \brief The Notification class.
///

class Notification : public TextObject
{
    friend class NotificationManager;

    const float lifeTime = 1000.f;
    float age;

    virtual void onAwake() override;
};


///
/// \brief The NotificationManager class.
///

class NotificationManager : public UIObject
{
    list<Notification*> notifications;

    //engine
    virtual void onUpdate(float) override;

public:
    //action
    void message(const string&);
};

#endif // NOTIFICATION_H
