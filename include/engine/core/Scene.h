#ifndef SCENE_H
#define SCENE_H

#include "engine/object/Object.h"
#include "engine/component/Renderable.h"
#include "engine/core/CollisionManager.h"

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <unordered_set>
#include <list>

using namespace std;

class Camera;
class Engine;


//Alias for the main objects map type [renderLayer, hashID, id, obj_ptr]
using OBJ_MAP_TYPE = map<unsigned int, map<size_t, map<unsigned int, shared_ptr<Object>>>>;






///
/// \brief Helper class for Scene class.
///

class ObjectFidingHelper
{

    //friend
    friend class Scene;



    //find object with hash_id and id

    template <typename T>
    T* findObject(const OBJ_MAP_TYPE& objects, const size_t& hash_id, const unsigned int& id)
    {
        Object* _obj = nullptr;
        T* _objT = nullptr;

        //search
        for (const auto& p_l : objects)
        {
            auto outerIt = p_l.second.find(hash_id);
            if (outerIt != p_l.second.end())
            {
                auto innerIt = outerIt->second.find(id);
                if (innerIt != outerIt->second.end())
                {
                    _obj = innerIt->second.get();

                    if (!_obj->isEnable()) {
                        continue;
                    }

                    _objT = dynamic_cast<T*>(_obj);
                    break;
                }
            }
        }

        //error report
        if (_obj && !_objT)
        {
            VDebuger::print("SCENE :: FIND_OBJECT :: casted obj is nullptr:", typeid(_obj).name(), ">>", typeid(T).name());
        }

        return _objT;
    }



    //find object with tag

    template <typename T>
    T* findObject(const OBJ_MAP_TYPE& objects, const string& tag, bool polimorficAllowed)
    {
        size_t t_hashID = typeid(T).hash_code();

        for (const auto& layerPair : objects)
        {
            if (polimorficAllowed)
            {
                for (const auto& hashPair : layerPair.second)
                {
                    T* _obj = findObjectWithTagHelper<T>(hashPair.second, tag);

                    if (_obj)
                    {
                        return _obj;
                    }
                }
            }
            else
            {
                auto hashPair = layerPair.second.find(t_hashID);
                if (hashPair == layerPair.second.end())
                {
                    break;
                }

                return findObjectWithTagHelper<T>(hashPair->second, tag);
            }
        }

        return nullptr;
    }



    //find object with tag helper

    template <typename T>
    T* findObjectWithTagHelper(const map<unsigned int, shared_ptr<Object>>& objMap, const std::string& tag)
    {
        for (const auto& objPair : objMap)
        {
            Object* _objPtr = objPair.second.get();

            if (!_objPtr->isEnable()) {
                continue;
            }

            //tag check
            if (!tag.empty() && !_objPtr->checkTag(tag))
            {
                continue;
            }

            return dynamic_cast<T*>(_objPtr);
        }

        return nullptr;
    }



    //find objects with tag

    template <typename T>
    vector<T*> findObjects(const OBJ_MAP_TYPE& objects, const string& tag, bool polimorficAllowed)
    {
        size_t t_hashID = typeid(T).hash_code();

        vector<T*> outVec;
        if (outVec.capacity() < objects.size()) {
            outVec.reserve(objects.size());
        }

        for (const auto& layerPair : objects)
        {
            for (const auto& hashPair : layerPair.second)
            {
                for (const auto& objPair : hashPair.second)
                {
                    Object* _objPtr = objPair.second.get();

                    if (!_objPtr->isEnable()) {
                        continue;
                    }

                    //tag check
                    if (!tag.empty() && !_objPtr->checkTag(tag))
                    {
                        continue;
                    }

                    if (T* castedObj = dynamic_cast<T*>(_objPtr))
                    {
                        if (_objPtr->getHashID() == t_hashID)
                        {
                            outVec.push_back(castedObj);
                        }
                        else if (polimorficAllowed)
                        {
                            outVec.push_back(castedObj);
                        }
                    }
                }
            }
        }

        return outVec;
    }

};








///
/// \brief Base class for all scenes. Every scene must inherit from this class.
/// \details Remember to implement the abstract method !!!
///

class Scene
{
    friend class Engine;

private:
    Engine* game;
    Camera* mainCamera;
    string name;

    bool m_isThisFirstFrame;
    float globalScale; //the scaling factor of all objects during creation
    unsigned int next_id_for_go;

    unique_ptr<CollisionManager> collisionManager;

    OBJ_MAP_TYPE objects;
    unordered_set<shared_ptr<Object>> WIDeadBodyCleanupCell;
    list<shared_ptr<Object>> buffor_objectsToCreate;
    unordered_set<Object*> buffor_objectsToKill;

public:
    Scene();
    ~Scene();
    void init(Engine* game, const string& name, unsigned int chunkSize);

private:
    void load();
    void dispose();

    //objects operations
    void forEachObject(const function<void(Object*)>& func);
    void callOnStartOnObjects();
    void callOnUpdateOnObjects(float deltaTime);
    void refreshStatesOnObjects();
    void callOnLateUpdateOnObjects(float deltaTime);
    void spawnObjectsFromBuffor();
    bool spawnObjectsFromBufforHelper(const shared_ptr<Object>&);
    void killObjectsFromBuffor();

protected:

    ///
    /// \brief Method for creating objects placed by default on the scene and setting their default parameters.
    /// \details More information about object creation in the description of createObject<T>() method.
    ///

    virtual void loadObjects() = 0;


public:

    ///
    /// \brief Restores the scene to default state
    ///

    void reload();


    ///
    /// \brief Returns true if there are no objects on the scene.
    /// \return bool
    ///

    const bool isEmpty() const;


    ///
    /// \brief Returns true if this is the first frame since loading this scene.
    /// \return bool
    ///

    const bool isThisFirstFrame() const;


    //setters
    void set_mainCamera(Camera*);
    void set_globalScale(const float&);

    //getters
    Engine* getGame() const;
    Camera* get_mainCamera() const;
    const string& get_name() const;
    const float& get_globalScale() const;
    const OBJ_MAP_TYPE& get_objects() const;
    CollisionManager* get_collisionManager() const;

private:
    void update(float deltaTime); //This method is called by the engine.


public:

    ///
    /// \brief A method that removes an object from the scene.
    /// \param Object* A pointer to the object we want to remove from the scene.
    /// \param critical A flag that determines whether the object should be completely removed from memory [critical = true]
    /// or safely moved to the WIDeadBodyCleanupCell collection [critical = false] (recommended).
    ///

    void killObject(Object*, bool critical = false);


    //Methods that search for objects by hash_id and id.
    Object* findObject(const size_t& hash_id, const unsigned int& id);
    GameObject* findGameObject(const size_t& hash_id, const unsigned int& id);
    UIObject* findUIObject(const size_t& hash_id, const unsigned int& id);

    //Methods that search for objects by tag.
    GameObject* findGameObject(const string& tag);
    UIObject* findUIObject(const string& tag);
    vector<GameObject*> findGameObjects(const string& tag);
    vector<UIObject*> findUIObjects(const string& tag);



    // Template methods.

public:

    ///
    /// \brief This method is for creating objects and adding them to the scene.
    /// The method returns a raw pointer to the created object.
    /// After the program ends, memory is freed automatically. DO NOT CLEAN THE POINTER MANUALLY WITH DELETE.
    /// To create an object:
    /// 1. Create a class that publicly inherits from Object, for example: class Entity.
    /// 2. Call the createObject<Entity>() method anywhere to make the object appear in the scene.
    /// To create an object that appears in the scene by default, use the loadObjects() method.
    /// \tparam T Type that publicly inherits from the Object class.
    /// \param _renderLayer The layer on which the object will be rendered.
    /// \param _parent The parent object of the object being created.
    /// \return T*
    ///

    template <typename T>
    typename enable_if<is_base_of<Object, T>::value, T*>::type
    createObject(unsigned int _renderLayer = 0, Object* _parent = nullptr)
    {
        shared_ptr<Object> go_ptr = make_shared<T>();

        //init
        go_ptr->setParent(_parent);
        bool m_init = go_ptr->init(
            this->game,
            _renderLayer,
            typeid(T).hash_code(),
            next_id_for_go++
            );

        //scaling
        if (Transform* _t = go_ptr->transform) {
            _t->scaleBy(this->globalScale);
        }

        if (!m_init)
        {
            VDebuger::print("<ERROR> :: SCENE :: CREATE_OBJECT :: go init error");

            return nullptr;
        }

        //add
        if (m_isThisFirstFrame)
        {
            objects[_renderLayer][go_ptr->hashId][go_ptr->id] = go_ptr;
            go_ptr->setEnable(true);

            //log
            VDebuger::print("SCENE_MANAGER :: obj:", go_ptr.get(), "id =", go_ptr->id, "hash_id =", go_ptr->hashId, "added to scene:", this->name);
        }
        else
        {
            buffor_objectsToCreate.push_back(go_ptr);

            //log
            VDebuger::print("SCENE_MANAGER :: obj:", go_ptr.get(), "id =", go_ptr->id, "hash_id =", go_ptr->hashId, "added to buffor in scene:", this->name);
        }

        //call awake()
        go_ptr->onAwake();

        return dynamic_cast<T*>(go_ptr.get());
    }

    ///
    /// \brief Template method that searches for an object in the scene by its hash_id and id.
    /// \tparam T Type that publicly inherits from the Object class.
    /// \param hash_id The object's hash_id.
    /// \param id The object's id.
    /// \return T*
    ///

    template <typename T>
    typename enable_if<is_base_of<Object, T>::value, T*>::type
    findObject(const size_t& hash_id, const unsigned int& id)
    {
        ObjectFidingHelper obj;
        return obj.findObject<T>(this->objects, hash_id, id);
    }

    ///
    /// \brief Template method that searches for and returns a single object in the scene by its tag.
    /// \tparam T Type that publicly inherits from the Object class.
    /// \param tag One of the tags assigned to the object.
    /// \param polimorficAllowed Flag that determines if objects publicly inheriting from class T are included.
    /// \return T*
    ///

    template <typename T>
    typename enable_if<is_base_of<Object, T>::value, T*>::type
    findObject(const string& tag = string(), bool polimorficAllowed = false)
    {
        ObjectFidingHelper obj;
        return obj.findObject<T>(this->objects, tag, polimorficAllowed);
    }

    ///
    /// \brief Template method that searches for and returns multiple objects in the scene by their tag.
    /// \tparam T Type that publicly inherits from the Object class.
    /// \param tag One of the tags assigned to the object.
    /// \param polimorficAllowed Flag that determines if objects publicly inheriting from class T are included.
    /// \return T*
    ///

    template <typename T>
    typename enable_if<is_base_of<Object, T>::value, vector<T*>>::type
    findObjects(const string& tag = string(), bool polimorficAllowed = false)
    {
        ObjectFidingHelper obj;
        return obj.findObjects<T>(this->objects, tag, polimorficAllowed);
    }
};

#endif // SCENE_H
