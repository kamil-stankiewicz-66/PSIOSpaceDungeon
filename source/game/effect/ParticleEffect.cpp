#include "game/effect/ParticleEffect.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"




///
/// converters
///

static float vectorToAngle(const Vector2& v) {
    return std::atan2(v.y, v.x) * 180.0f / M_PI;
}

static Vector2 angleToVector(float angle_deg) {
    float angle_rad = angle_deg * M_PI / 180.0f;
    return Vector2(std::cos(angle_rad), std::sin(angle_rad));
}




///
/// helpers
///

Vector2 ParticleEffect::getRndDir(const Vector2& dir)
{
    float baseAngle = vectorToAngle(dir);
    uniform_real_distribution<float> dist(-spread * 0.5f, spread * 0.5f);
    float angleOffset = dist(rng);
    float finalAngle = baseAngle + angleOffset;
    return angleToVector(finalAngle);
}

float ParticleEffect::getRndFloat(const float& val, const float& diff)
{
    if (diff > 0.0f)
    {
        uniform_real_distribution<float> dist(val - diff * 0.5f, val + diff * 0.5f);
        return dist(rng);
    }
    else
    {
        return val;
    }
}

uint ParticleEffect::getRndUInt(const uint& val, const uint& diff)
{
    if (diff > 0u)
    {
        uniform_int_distribution<uint> dist(val - (diff * 0.5f), val + (diff * 0.5f));
        return dist(rng);
    }
    else
    {
        return val;
    }
}




///
/// engine
///


void ParticleEffect::onUpdate(float dt)
{
    //update
    for (auto& particle : particles)
    {
        particle->pos += particle->dir * 0.075f * dt * particle->speed;
        particle->age += dt;

        //render
        particle->render(getGame(), particle->pos, scale, vectorToAngle(particle->dir), false, false);
    }


    //delete old particles
    particles.erase(remove_if(particles.begin(), particles.end(),
                                   [](const unique_ptr<Particle>& p){ return p->age >= p->lifeTime; }), particles.end());


    //auto destroy
    if (m_autoDestroy && particles.empty()) {
        getGame()->get_currentScene()->killObject(this, true);
    }
}




///
/// invoke
///


void ParticleEffect::invoke(const Vector2& dir, bool autoDestroy)
{
    if (autoDestroy) {
        m_autoDestroy = true;
    }

    uint N = getRndUInt(this->particleNum, this->particleNum_diff);
    particles.reserve(particles.size() + N);

    for (uint n = 0u; n < N; ++n)
    {
        auto particle = make_unique<Particle>();

        particle->setTexture(TextureBase::get(this->texture_ref));
        particle->setColor(this->color);

        particle->dir = getRndDir(dir);
        particle->speed = getRndFloat(this->speed, this->speed_diff);
        particle->lifeTime = getRndFloat(this->lifeTime, this->lifeTime_diff);
        particle->pos = getTransformPtr()->get_position();

        particles.emplace_back(std::move(particle));
    }
}




///
/// setter
///


void ParticleEffect::setTexture(const string_view tex) {
    texture_ref = tex.data();
}

void ParticleEffect::setColor(const sf::Color& color) {
    this->color = color;
}

void ParticleEffect::setScale(const Vector2& scale) {
    this->scale = scale;
}

void ParticleEffect::setSpread(const float& s) {
    this->spread = s;
}

void ParticleEffect::setSpeed(const float& s) {
    this->speed = s;
}

void ParticleEffect::setSpeedDiff(const float& sd) {
    this->speed_diff = sd;
}

void ParticleEffect::setLifeTime(const float& l) {
    this->lifeTime = l;
}

void ParticleEffect::setLifeTimeDiff(const float& ld) {
    this->lifeTime_diff = ld;
}

void ParticleEffect::setParticleNum(const uint& pn) {
    this->particleNum = pn;
}

void ParticleEffect::setParticleNumDiff(const uint& pnd) {
    this->particleNum_diff = pnd;
}
