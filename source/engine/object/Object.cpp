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
    parent(nullptr),
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




///
/// hierarchy
///


void Object::setParent(Object* arg_parent)
{
    if (!arg_parent)
        return;

    if (this->isChild())
        this->dispose_asChild();

    arg_parent->addChild(this);
}

void Object::addChild(Object* arg_child)
{
    if (!arg_child)
        return;

    if (arg_child->isChild())
        arg_child->dispose_asChild();

    for (const Object* _child : this->childs)
    {
        if (_child == arg_child)
            return;
    }

    arg_child->parent = this;
    this->childs.push_back(arg_child);
}

void Object::dispose_asChild()
{
    if (!this->parent)
    {
        return;
    }

    auto it = find(this->parent->childs.begin(), this->parent->childs.end(), this);
    if (it != this->parent->childs.end()) {
        this->parent->childs.erase(it);
    }

    this->parent = nullptr;
}

void Object::dispose_childs()
{
    vector<Object*> _childsCopy = this->childs;
    for (Object* _child : _childsCopy)
    {
        if (_child)
            _child->dispose_asChild();
    }
}


const Object* Object::getParent() const {
    return this->parent;
}

const std::vector<Object*>& Object::getChilds() const {
    return this->childs;
}


bool Object::isChild()
{
    return this->parent != nullptr;
}

bool Object::isChildOf(Object* _object)
{
    if (this->isChild())
    {
        if (this->parent == _object ||
            this->parent->isChildOf(_object))
        {
            return true;
        }
    }

    return false;
}

bool Object::try_getParent(Object*& out)
{
    if (this->isChild())
    {
        out = this->parent;
        return true;
    }

    return false;
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
