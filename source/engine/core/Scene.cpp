#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "engine/object/Camera.h"

Scene::Scene()
    : game(nullptr), mainCamera(nullptr), name(""), globalScale(1.0f), next_id_for_go(0), m_isThisFirstFrame(true)
{

}

Scene::~Scene()
{
    bool m_flag(false);

#ifndef NDEBUG
    for (auto& p_l : objects)
    {
        for (auto& p_o : p_l.second)
        {
            for (auto& p_i : p_o.second)
            {
                if (p_i.second.unique()) {
                    m_flag = true;
                    break;
                }
            }

            if (m_flag)
                break;
        }

        if (m_flag)
            break;
    }


    if (m_flag)
    {
        VDebuger::print("\nSCENE :: DESTRUCTOR :: scene", this, "name =", this->name, "{");
    }
#endif

    objects.clear();

    if (m_flag)
    {
        VDebuger::print("}\n");
    }

}


void Scene::init(Engine* arg_game, const string& arg_name, unsigned int arg_chunkSize)
{
    this->game = arg_game;
    this->name = arg_name;

    // collision manager init
    this->collisionManager = make_unique<CollisionManager>();
    this->collisionManager->init(this, arg_chunkSize);
}


void Scene::load()
{
    if (!this->isEmpty())
    {
        VDebuger::print("<WARNING> :: SCENE :: LOAD :: Cannot load a scene that is already loaded. To reload, call Scene::reload()");

        return;
    }


    //log
    VDebuger::print("SCENE :: LOAD :: scene", this->name, "loading started");


    //load
    this->loadObjects();


    //log
    VDebuger::print("SCENE :: LOAD :: scene", this->name, "loading completed");

}

void Scene::dispose()
{
    VDebuger::print("SCENE :: DISPOSE :: scene", this->name, "dispose started");

    this->objects.clear();
    this->buffor_objectsToCreate.clear();
    this->buffor_objectsToKill.clear();
    this->next_id_for_go = 0;
    this->m_isThisFirstFrame = true;
    this->WIDeadBodyCleanupCell.clear();
    this->collisionManager->dispose();

    VDebuger::print("SCENE :: DISPOSE :: scene", this->name, "dispose completed");
}





///
/// objects operations
///

void Scene::forEachObject(const function<void(Object*)>& func)
{
    for (const auto& renderLayerPair : objects)
    {
        const auto& hashMap = renderLayerPair.second;
        for (const auto& hashIDPair : hashMap)
        {
            const auto& idMap = hashIDPair.second;
            for (const auto& idPair : idMap)
            {
                const auto& obj = idPair.second;
                func(obj.get());
            }
        }
    }
}

void Scene::callOnStartOnObjects()
{
    //log
    VDebuger::print("SCENE :: LOAD :: calling start() on objects in scene:", this->name, "started");


    //call start
    forEachObject([](Object* obj)
                  {
                      if (obj)
                      {
                          obj->callOnStartInComponents();
                          obj->onStart();
                      }
                  });


    //log
    VDebuger::print("SCENE :: LOAD :: calling start() on objects in scene:", this->name, "completed");
}

void Scene::callOnUpdateOnObjects(float deltaTime)
{
    forEachObject([&deltaTime](Object* obj)
                  {
                      if (obj)
                      {
                          obj->callOnUpdateInComponents(deltaTime);
                          obj->onUpdate(deltaTime);
                      }
                  });
}

void Scene::callOnLateUpdateOnObjects(float deltaTime)
{
    forEachObject([&deltaTime](Object* obj)
                  {
                      if (obj)
                      {
                          obj->callOnLateUpdateInComponents(deltaTime);
                      }
                  });
}

void Scene::spawnObjectsFromBuffor()
{
    for (const auto& newObj : buffor_objectsToCreate)
    {
        if (!newObj) {
            continue;
        }

        //try add
        bool _result = spawnObjectsFromBufforHelper(newObj);

        //log
        if (_result)
        {
            newObj->setEnable(true);

            VDebuger::print("SCENE_MANAGER :: SPAWN_OBJECT_FROM_BUFFOR :: obj:", newObj.get(), "id =", newObj->id, "hash_id =", newObj->hashId, "added to scene:", this->name);
        }
        else
        {
            VDebuger::print("<ERROR> :: SCENE_MANAGER :: SPAWN_OBJECT_FROM_BUFFOR :: obj:", newObj.get(), "id =", newObj->id, "hash_id =", newObj->hashId, "adding to scene:", this->name);
        }
    }

    buffor_objectsToCreate.clear();
}

bool Scene::spawnObjectsFromBufforHelper(const shared_ptr<Object>& newObj)
{
    auto renderLayer = newObj->getRenderLayer();
    auto hashID = newObj->getHashID();
    auto id = newObj->getID();


    auto it_renderLayer = objects.find(renderLayer);

    if (it_renderLayer == objects.end())
    {
        objects.emplace(renderLayer, map<size_t, map<unsigned int, shared_ptr<Object>>>	{
                                         {hashID, { {id, newObj} }}
                                     });

        return true;
    }


    auto& hashMap = it_renderLayer->second;
    auto it_hashLayer = hashMap.find(hashID);

    if (it_hashLayer == hashMap.end())
    {
        hashMap.emplace(hashID, map<unsigned int, shared_ptr<Object>> {
                                    {id, newObj}
                                });

        return true;
    }


    auto& idMap = it_hashLayer->second;
    auto it_idLayer = idMap.find(id);

    if (it_idLayer == idMap.end())
    {
        idMap.emplace(id, newObj);

        return true;
    }


    return false;
}

void Scene::killObjectsFromBuffor()
{
    for (auto& objectToKill : this->buffor_objectsToKill)
    {
        if (!objectToKill) {
            continue;
        }

        //get render layer
        unsigned int renderLayer = objectToKill->getRenderLayer();

        //set object state
        objectToKill->set_state(ObjectState::PermaDead);

        //delete object
        auto it = objects[renderLayer][objectToKill->hashId].find(objectToKill->id);
        if (it != objects[renderLayer][objectToKill->hashId].end()) {
            objects[renderLayer][objectToKill->hashId].erase(it);
        }
    }

    buffor_objectsToKill.clear();
}

void Scene::refreshStatesOnObjects()
{
    for (const auto& renderLayerPair : objects)
    {
        for (const auto& hashIDPair : renderLayerPair.second)
        {
            for (const auto& idPair : hashIDPair.second)
            {
                Object* object = idPair.second.get();

                if (!object) {
                    return;
                }

                if (object->getState() == ObjectState::Reborn) {
                    object->set_state(ObjectState::Normal);
                }
                else if (object->getState() == ObjectState::Undead) {
                    object->set_state(ObjectState::Dead);
                }
            }
        }
    }
}





///
/// scene
///

void Scene::reload()
{
    VDebuger::print("SCENE :: RELOAD :: scene", this->name, "reload started");

    this->dispose();
    this->load();

    VDebuger::print("SCENE :: RELOAD :: scene", this->name, "reload completed");
}


const bool Scene::isEmpty() const {
    return this->objects.empty();
}

const bool Scene::isThisFirstFrame() const {
    return this->m_isThisFirstFrame;
}





///
/// setters
///

void Scene::set_mainCamera(Camera* _camera)
{
    if (!_camera)
    {
        return;
    }

    if (!this->findObject(_camera->getHashID(), _camera->getID()))
    {
        VDebuger::print("SCENE :: SET_MAIN_CAMERA :: This camera does not exist on the scene: ", this->name);

        return;
    }

    this->mainCamera = _camera;
}

void Scene::set_globalScale(const float& _gs)
{
    this->globalScale = _gs;
}





///
/// getters
///

Engine *Scene::getGame() const {
    return this->game;
}

Camera* Scene::get_mainCamera() const
{
    return this->mainCamera;
}

const string& Scene::get_name() const {
    return this->name;
}

const float& Scene::get_globalScale() const {
    return this->globalScale;
}

const OBJ_MAP_TYPE& Scene::get_objects() const {
    return this->objects;
}

CollisionManager* Scene::get_collisionManager() const {
    return collisionManager.get();
}





///
/// update all
///

void Scene::update(float deltaTime)
{
    if (m_isThisFirstFrame)
    {
        callOnStartOnObjects();
        m_isThisFirstFrame = false;
    }

    spawnObjectsFromBuffor();

    this->collisionManager->updateAll();

    killObjectsFromBuffor();

    //normal, undead, dead, reborn ...
    refreshStatesOnObjects();

    callOnUpdateOnObjects(deltaTime);
    callOnLateUpdateOnObjects(deltaTime);
}





///
/// kill
///

void Scene::killObject(Object* go, bool critical)
{
    if (go)
    {
        go->setEnable(false);
        buffor_objectsToKill.emplace(go);

        if (!critical)
        {
            WIDeadBodyCleanupCell.emplace(objects[go->getRenderLayer()][go->hashId][go->id]);

            VDebuger::print("SCENE :: KILLOBJECT :: safetly removed obj:", go->getLog());
        }
    }
}





///
/// find by hash_id and id
///

Object* Scene::findObject(const size_t& hash_id, const unsigned int& id)
{
    return findObject<Object>(hash_id, id);
}

GameObject* Scene::findGameObject(const size_t& hash_id, const unsigned int& id)
{
    return findObject<GameObject>(hash_id, id);
}

UIObject* Scene::findUIObject(const size_t& hash_id, const unsigned int& id)
{
    return findObject<UIObject>(hash_id, id);
}




///
/// find by tag
///

GameObject* Scene::findGameObject(const string& tag)
{
    return findObject<GameObject>(tag, true);
}

UIObject* Scene::findUIObject(const string& tag)
{
    return findObject<UIObject>(tag, true);
}

vector<GameObject*> Scene::findGameObjects(const string& tag)
{
    return findObjects<GameObject>(tag, true);
}

vector<UIObject*> Scene::findUIObjects(const string& tag)
{
    return findObjects<UIObject>(tag, true);
}
