#include "engine/core/Scene.h"
#include "engine/core/Debuger.h"

Scene::Scene()
    : game(nullptr), name(""), m_isThisFirstFrame(true)
{

}

Scene::~Scene()
{

}


void Scene::init(Engine* arg_game, const string& arg_name, unsigned int arg_chunkSize)
{
    this->game = arg_game;
    this->name = arg_name;
}


void Scene::load()
{
    //log
    VDebuger::print("SCENE :: LOAD :: scene", this->name, "loading completed");

}

void Scene::dispose()
{
    VDebuger::print("SCENE :: DISPOSE :: scene", this->name, "dispose started");

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


const bool Scene::isThisFirstFrame() const {
    return this->m_isThisFirstFrame;
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

