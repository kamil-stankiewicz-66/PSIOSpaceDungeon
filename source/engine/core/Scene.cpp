#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "engine/core/Debuger.h"

Scene::Scene()
    : game(nullptr), name(""), globalScale(1.0f), m_isThisFirstFrame(true)
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
    this->m_isThisFirstFrame = true;

    VDebuger::print("SCENE :: DISPOSE :: scene", this->name, "dispose completed");
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

void Scene::set_globalScale(const float& _gs)
{
    this->globalScale = _gs;
}





///
/// getters
///

const Engine* Scene::getGame() const {
    return this->game;
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





///
/// engine
///

void Scene::update(float deltaTime)
{
    if (m_isThisFirstFrame)
    {
        m_isThisFirstFrame = false;
    }
}

