#include "engine/core/Event.h"

void VEvent::addListener(const std::function<void()>& newListener)
{
    if (newListener == nullptr) {
        return;
    }

    this->listeners.emplace_back(newListener);
}

void VEvent::dispose()
{
    this->listeners.clear();
}

void VEvent::invoke()
{
    for (const auto& func : this->listeners)
    {
        if (func == nullptr) {
            continue;
        }

        func();
    }
}
