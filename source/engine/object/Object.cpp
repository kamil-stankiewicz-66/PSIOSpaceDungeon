#include "engine/object/Object.h"
#include "engine/core/Debuger.h"

#include <algorithm>


void Object::onStart() {}
void Object::onAwake() {}
void Object::onUpdate(float deltaTime) {}


void Object::set_state(ObjectState _state)
{
    if (m_state == ObjectState::PermaDead) {
        return;
    }

    this->m_state = _state;
}


Object::Object() :
    m_enable(false),
    game(nullptr),
    hashId(0), id(0)
{
}

Object::~Object()
{
    VDebuger::print("OBJECT :: DESTRUCTOR :: obj:", this, "hash_id =", this->hashId, "id =", this->id, "-> destroyed");
}


bool Object::init(Engine* game, const size_t& hashID, const unsigned int& id)
{
    if (!game)
    {
        VDebuger::print("<ERROR> :: OBJECT :: INIT :: game is nullptr");

        return false;
    }

    this->game = game;
    this->hashId = hashID;
    this->id = id;

    return true;
}




Engine* Object::getGame() const {
    return this->game;
}


void Object::setEnable(bool _b)
{
    if (_b == m_enable || m_state == ObjectState::PermaDead) {
        return;
    }

    bool _preEnable = m_enable;
    m_enable = _b;

    if (!_preEnable && m_enable)
    {
        m_state = ObjectState::Reborn;
    }
    else if (_preEnable && !m_enable)
    {
        m_state = ObjectState::Undead;
    }
}

const bool Object::isEnable() const {
    return this->m_enable;
}

const ObjectState& Object::getState() const {
    return this->m_state;
}







const size_t& Object::getHashID() const {
    return this->hashId;
}

const unsigned int& Object::getID() const {
    return this->id;
}











GameObject::GameObject()
{

}



UIObject::UIObject()
{

}
