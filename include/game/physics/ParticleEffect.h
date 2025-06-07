#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "engine/component/Renderable.h"
#include "engine/object/Object.h"
#include <random>

class Particle : public VSprite
{
    friend class ParticleEffect;

    //to set
    Vector2 dir;
    float speed;
    float lifeTime;

    //calculation
    Vector2 pos;
    float age;
};

class ParticleEffect : public GameObject
{
    vector<unique_ptr<Particle>> particles;

    bool m_autoDestroy;

    shared_ptr<sf::Texture> texture;
    sf::Color color;
    Vector2 scale;

    float spread;

    float speed;
    float speed_diff;

    float lifeTime;
    float lifeTime_diff;

    uint particleNum;
    uint particleNum_diff;

    //random engine
    mt19937 rng;

    //helpers
    Vector2 getRndDir(const Vector2& dir);
    float getRndFloat(const float& val, const float& diff);
    uint getRndUInt(const uint& val, const uint& diff);

    //engine
    virtual void onUpdate(float dt) override;

public:

    ///
    /// \brief Emit particles.
    /// \param dir Base direction.
    /// \param autoDestroy True - object will be removed from the scene after emit ends
    ///

    void invoke(const Vector2& dir, bool autoDestroy = true);


    //setters
    void setTexture(const string_view textureRef);
    void setTexture(shared_ptr<sf::Texture>& texture);
    void setColor(const sf::Color& color);
    void setScale(const Vector2& scale);
    void setSpread(const float& spread);
    void setSpeed(const float& speed);
    void setSpeedDiff(const float& speed_diff);
    void setLifeTime(const float& lifeTime);
    void setLifeTimeDiff(const float& lifeTime_diff);
    void setParticleNum(const uint& particleNum);
    void setParticleNumDiff(const uint& particleNum_diff);
};

#endif // PARTICLEEFFECT_H
