#ifndef COMPONENT_H
#define COMPONENT_H

class Engine;
class Object;

typedef unsigned int uint;

///
/// \brief Structure storing execution priorities of selected components.
/// \details Components with the lowest value are executed first.
///

struct COMPONENT_PRIORITY
{
    static constexpr float TRANSFORM = -100.0f;
};

///
/// \brief Base class for all Components.
///

class Component
{
    friend class Object;

private:
    Engine* game;
    Object* object;
    uint type_hash_code;

public:
    const float	PRIORITY;

    Component(float PRIORITY = 0.0f);
    virtual ~Component();

    //getters
    const uint get_typeHashCode() const;
    Engine* getGame() const;
    Object* getObject() const;

protected:
    virtual bool init(Engine* game, Object* parent); //This method is called by the engine.


    /*
    * The methods are meant for storing your own custom logic.
    * They are empty by default.
    * These methods are called by the engine.
    */

    virtual void onAwake(); //when the Component is created.
    virtual void onStart(); //in the first frame after the scene loads.
    virtual void onUpdate(float deltaTime); //every frame.
    virtual void onLateUpdate(float deltaTime); //every frame, after onUpdate(float) runs for every object.

private:
    void onCreate(uint type_hash_code); //This method is called by the engine.

};

#endif // COMPONENT_H
