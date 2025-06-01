#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <set>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "engine/component/Component.h"
#include "engine/component/Renderable.h"
#include "engine/core/Debuger.h"
#include "engine/component/Transform.h"

using namespace std;

class Scene;
class Engine;
class VSprite;


///
/// \brief Enum representing different states of an object.
/// \details
/// Normal - object is active,
/// Undead - first frame after setActive(false)
/// Dead - object is not active
/// Reborn - first frame after setActive(true)
/// PermaDead - object has been removed from the scene and cannot be restored
///

enum class ObjectState
{
    Normal, Undead, Dead, Reborn, PermaDead
};

std::ostream& operator<<(std::ostream& os, ObjectState state);


///
/// \brief Base class for an object. Every game and interface object must be a kind of this class.
/// \details Instead of inheriting directly from Object, it is recommended to use GameObject for game objects and UIObject for interface objects.
///

class Object
{
    friend class Scene;

private:
    bool m_enable;
    ObjectState m_state;
    Engine* game;
    Object* parent;
    vector<Object*> childs;
    map<float, vector<shared_ptr<Component>>> components; //priority, vector
    size_t renderLayer;
    size_t hashId;
    unsigned int id;
    set<string> tags;

    bool init(Engine* game, const size_t& renderLayer, const size_t& hashID, const unsigned int& id); //This method is called by the engine.
    void set_state(ObjectState); //This method is called by the engine.

protected:
    //Methods for storing object logic defined by game developer
    //These methods are called by the engine...
    virtual void onStart(); //in first frame.
    virtual void onAwake(); //when object is created on scene.
    virtual void onUpdate(float deltaTime); //every frame.


public:
    Object();
    virtual ~Object();

    Engine* getGame() const;

    void setEnable(bool);
    const bool isEnable() const;
    const ObjectState& getState() const;


    //hierarchy

    void setParent(Object*);
    void addChild(Object*);
    void dispose_asChild();
    void dispose_childs();

    Object* getParent() const;
    const vector<Object*>& getChilds() const;

    bool isChild() const;
    bool isChildOf(Object*) const;
    bool try_getParent(Object*& out) const;


    //identify

    void setTags(const vector<string>&);
    void addTags(const vector<string>&);
    void addTag(const string&);
    void removeTag(const string&);

    const size_t& getRenderLayer() const;
    const size_t& getHashID() const;
    const unsigned int& getID() const;
    const set<string>& getTags() const;
    const string getTag(const unsigned char& index) const;

    const bool checkTag(const string&) const;


    //log

    const string getLog();


    //components

private:
    void callOnStartInComponents();
    void callOnUpdateInComponents(float deltaTime);
    void callOnLateUpdateInComponents(float deltaTime);

protected:

    //basic component
    Transform* transform;

public:

    ///
    /// \brief Method for creating components and adding them to objects.
    /// \details Memory is automatically freed when program ends. DO NOT MANUALLY DELETE THE POINTER.
    /// To create component call createComponent<TYPE>() on target object.
    /// Engine includes set of ready-to-use components and allows creating custom ones.
    /// \return Returns raw pointer to created component.
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, T*>::type
    createComponent()
    {
        bool m_error = false;
        bool m_transformExist = false;

        size_t type_hash_code = typeid(T).hash_code();
        ostringstream _message;

        for (const auto& p_v : components)
        {
            for (const auto& _c : p_v.second)
            {
                if (!m_transformExist && dynamic_cast<Transform*>(_c.get()))
                {
                    m_transformExist = true;
                }

                if (type_hash_code == _c->get_typeHashCode())
                {
                    _message
                        << "<ERROR> :: OBJECT :: CREATE_COMPONENT :: You cannot create second '"
                        << typeid(T).name()
                        << "' component in object: " << this;

                    m_error = true;
                    break;
                }
            }
        }

        if (m_transformExist && is_base_of<Transform, T>::value)
        {
            _message.str("");
            _message
                << "<ERROR> :: OBJECT :: CREATE_COMPONENT :: You cannot create more Transform components in object: " << this;

            m_error = true;
        }

        //report
        if (m_error)
        {
            VDebuger::print("<ERROR>",_message.str());
            throw runtime_error(_message.str());
            return nullptr;
        }


        shared_ptr<Component> _c = make_shared<T>();
        _c->onCreate(type_hash_code);
        _c->init(game, this);
        _c->onAwake();

        this->components[_c->PRIORITY].push_back(_c);

        T* _r = dynamic_cast<T*>(_c.get());
        return _r;
    }

    ///
    /// \brief Method for finding specific component in object.
    /// \details If component wasn't created in object, returns nullptr.
    /// \tparam T Class derived from Component class.
    /// \param polymorphicAllowed Flag determining if classes derived from T should be considered.
    /// \return Returns pointer to found component.
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, T*>::type
    getComponent(bool polimorhicAllowed = false)
    {
        for (const auto& p_v : this->components)
        {
            for (const auto& _comp : p_v.second)
            {
                if (polimorhicAllowed)
                {
                    if (T* _casted = dynamic_cast<T*>(_comp.get())) {
                        return _casted;
                    }
                }
                else if (typeid(T).hash_code() == _comp->get_typeHashCode())
                {
                    if (T* _casted = dynamic_cast<T*>(_comp.get())) {
                        return _casted;
                    }
                }
            }
        }

        return nullptr;
    }

    ///
    /// \brief Method for finding specific component in object.
    /// \details If component is found - overwrites reference with found component and returns true.
    /// If component is not found, returns false.
    /// \tparam T Class derived from Component class.
    /// \param out Reference to component pointer.
    /// \param polymorphicAllowed Flag determining if derived classes should be considered.
    /// \return True - if found, False - if not found.
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, bool>::type
    try_getComponent(T*& out, bool polimorhicAllowed = true)
    {
        return out = this->getComponent<T>(polimorhicAllowed);
    }


    //get basic component

    Transform* getTransformPtr();
};


///
/// \brief Class representing an empty object with sprite.
///

class SpriteObject : public Object
{
private:
    VSprite* sprite;

public:
    SpriteObject();
    VSprite* getSpritePtr() const;
};


///
/// \brief Class representing an empty game object.
///

class GameObject : public SpriteObject
{
public:
    GameObject();
};


///
/// \brief Class representing an empty interface (UI) object.
///

class UIObject : public SpriteObject
{
public:
    UIObject();
};


///
/// \brief Class representing an empty object with text.
///

class TextObject : public Object
{
private:
    VText* text;

public:
    TextObject();
    VText* getTextPtr() const;
};

#endif // OBJECT_H
