#include "engine/component/Component.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"


void Component::onAwake() {}
void Component::onStart() {}
void Component::onUpdate(float deltaTime) {}
void Component::onLateUpdate(float deltaTime) {}



Component::Component(float _PRIORITY) : PRIORITY(_PRIORITY), game(nullptr), object(nullptr), type_hash_code(0) {}
Component::~Component() {}



const uint Component::get_typeHashCode() const {
    return this->type_hash_code;
}

Engine* Component::getGame() const {
    return this->game;
}

Object* Component::getObject() const {
    return this->object;
}



bool Component::init(Engine* game, Object* arg_p)
{
    this->game = game;
    this->object = arg_p;
    return this->game && this->object;
}



void Component::onCreate(uint arg_typeHashCode)
{
    this->type_hash_code = arg_typeHashCode;
}
