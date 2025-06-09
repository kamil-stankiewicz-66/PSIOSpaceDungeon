#ifndef HEALTH_H
#define HEALTH_H

#include "game/core/ScriptableObject.h"
#include <algorithm>
#include <iostream>


class Health

{
private:
    float currentHealth = 0.0f; // ilosc hp w danym momencie
    float maxHealth = 0.0f; // maksymalne hp
    float regenRate = 0.0f; // autoregeneracja

    const HealthData* sourceData = nullptr;

public:
    Health() = default;

    void initFromID(uint healthID) {

        sourceData = HealthSO::get(healthID); //pobranie danych
        if (sourceData) {
            maxHealth = sourceData->maxHealth;
            currentHealth = maxHealth; //start z pelnym hp
            regenRate = sourceData->regenRate;
        } else {
            std::cerr << "[Health] Nie udalo sie zaladowac danych zdrowia dla ID = " << healthID << "\n";
        }
    }

    // Autoregeneracja
    void update(float dt) {
        if (regenRate > 0.0f && currentHealth < maxHealth) {
            currentHealth += regenRate * dt;
            currentHealth = std::min(currentHealth, maxHealth);
        }
    }

    //Odejmowanie hp
    void takeDamage(float dmg) {
        if (dmg > 0.0f) {
            currentHealth -= dmg;
            currentHealth = std::max(currentHealth, 0.0f);
        }
    }

    //Leczenie reczne
    bool heal(float amount) {
        if (amount > 0.0f && currentHealth < maxHealth) {
            currentHealth += amount;
            currentHealth = std::min(currentHealth, maxHealth); // ograniczenie
            return true; // leczenie sie udalo
        }
        return false; // nie ma sensu leczyc
    }

    // Sprawdzenie czy jednostka zyje
    bool isDead() const {
        return currentHealth <= 0.0f;
    }

    float getHealth() const {
        return currentHealth;
    }

    float getMaxHealth() const {
        return maxHealth;
    }

    const HealthData* getSourceData() const {
        return sourceData;
    }
};

#endif // HEALTH_H
