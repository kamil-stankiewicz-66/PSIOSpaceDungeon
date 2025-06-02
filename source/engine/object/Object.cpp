#include "engine/object/Object.h"
#include "engine/core/Debuger.h"
#include "engine/component/Renderable.h"

#include <algorithm>



std::ostream& operator<<(std::ostream& os, ObjectState state)
{
    switch (state) {
    case ObjectState::Normal: os << ">Normal<"; break;
    case ObjectState::Undead: os << ">Undead<"; break;
    case ObjectState::Dead: os << ">Dead<"; break;
    case ObjectState::Reborn: os << ">Reborn<"; break;
    case ObjectState::PermaDead: os << ">PermaDead<"; break;
    default: os << ">Unknown<"; break;
    }

    return os;
}



void Object::onStart() {}
void Object::onAwake() {}
void Object::onUpdate(float deltaTime) {}


void Object::set_state(ObjectState _state)
{
    if (m_state == ObjectState::PermaDead) {
        return;
    }

    this->m_state = _state;

    VDebuger::print("OBJECT :: SETSTATE :: set state", this->m_state, "on obj:", this->getLog());
}


Object::Object() :
    m_enable(false),
    game(nullptr),
    parent(nullptr),
    hashId(0), id(0),
    transform(nullptr)
{

}

Object::~Object()
{
    VDebuger::print("OBJECT :: DESTRUCTOR :: obj:", this->getLog());
}


bool Object::init(Engine* game, const size_t& renderLayer, const size_t& hashID, const unsigned int& id)
{
    if (!game)
    {
        VDebuger::print("<ERROR> :: OBJECT :: INIT :: game is nullptr");

        return false;
    }

    this->game = game;
    this->renderLayer = renderLayer;
    this->hashId = hashID;
    this->id = id;

    //comps
    for (const auto& p_v : this->components)
    {
        for (const auto& _comp : p_v.second)
        {
            if (!_comp->init(this->game, this))
            {
                VDebuger::print("<ERROR> :: OBJECT :: INIT :: comp init error");

                return false;
            }
        }
    }

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

    if (arg_child->transform) {
        arg_child->transform->resetPosition();
    }

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

    this->transform->updateGlobalTransform();
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


Object* Object::getParent() const {
    return this->parent;
}

const std::vector<Object*>& Object::getChilds() const {
    return this->childs;
}


bool Object::isChild() const
{
    return this->parent != nullptr;
}

bool Object::isChildOf(Object* _object) const
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

bool Object::try_getParent(Object*& out) const
{
    if (this->isChild())
    {
        out = this->parent;
        return true;
    }

    return false;
}




///
/// identify
///


void Object::setTags(const vector<string>& arg_tags)
{
    if (!this->tags.empty())
        this->tags.clear();

    addTags(arg_tags);
}

void Object::addTags(const vector<string>& arg_tags)
{
    for (const auto& _t : arg_tags)
        addTag(_t);
}

void Object::addTag(const string& arg_tag)
{
    this->tags.emplace(arg_tag);
}

void Object::removeTag(const string& arg_tag)
{
    auto it = this->tags.find(arg_tag);
    if (it != this->tags.end())
    {
        this->tags.erase(it);
    }
}


const size_t& Object::getRenderLayer() const {
    return this->renderLayer;
}

const size_t& Object::getHashID() const {
    return this->hashId;
}

const unsigned int& Object::getID() const {
    return this->id;
}

const set<string>& Object::getTags() const {
    return this->tags;
}

const string Object::getTag(const unsigned char& index) const
{
    if (this->tags.size() <= index)
        return "<ERROR>_TAG_OUT_OF_INDEX";

    auto it = this->tags.begin();
    advance(it, index);
    return *it;
}


const bool Object::checkTag(const string& arg_tag) const {
    return this->tags.find(arg_tag) != this->tags.end();
}



const string Object::getLog()
{
    std::ostringstream oss;
    oss << this << ", render_layer: " << this->getRenderLayer()
        << ", hash_id = " << this->hashId
        << ", id = " << this->id
        << ", tag[0]: " << getTag(0);

    return oss.str();
}




///
/// components
///


void Object::callOnStartInComponents()
{
    for (const auto& p_v : this->components)
    {
        for (const auto& _comp : p_v.second)
        {
            if (_comp != nullptr)
                _comp->onStart();
        }
    }
}

void Object::callOnUpdateInComponents(float _deltaTime)
{
    for (const auto& p_v : this->components)
    {
        for (const auto& _comp : p_v.second)
        {
            if (_comp != nullptr)
                _comp->onUpdate(_deltaTime);
        }
    }
}

void Object::callOnLateUpdateInComponents(float _deltaTime)
{
    for (const auto& p_v : this->components)
    {
        for (const auto& _comp : p_v.second)
        {
            if (_comp != nullptr)
                _comp->onLateUpdate(_deltaTime);
        }
    }
}


Transform* Object::getTransformPtr() {
    return this->transform;
}



///
/// Sprite object
///

SpriteObject::SpriteObject() : sprite(nullptr)
{
    this->sprite = createComponent<VSprite>();
}

VSprite *SpriteObject::getSpritePtr() const {
    return this->sprite;
}



///
/// GameObject
///

GameObject::GameObject()
{
    this->transform = createComponent<Transform>();
}



///
/// GameObject
///

UIObject::UIObject()
{
    this->transform = createComponent<RectTransform>();
}



///
/// TextObject
///

TextObject::TextObject() : text(nullptr)
{
    this->transform = createComponent<RectTransform>();
    this->text = createComponent<VText>();
}

VText* TextObject::getTextPtr() const {
    return this->text;
}
