//
// Created by HardcoreAxolotl on 10/08/2026.
//

#ifndef ASTROIDS_BULLETMANAGER_HPP
#define ASTROIDS_BULLETMANAGER_HPP

#include <array>

#include "Bullet.hpp"

class Player;

class BulletManager {
    std::array<Bullet, 100> bullets;
    float bullet_speed = 400.0f; // pixels per second
    public:

    BulletManager();
    void SpawnBullet(Player *player);
    void UpdateBullets(float delta_time);
    void RenderBullets(SDL_Renderer *renderer, bool debug);
};


#endif //ASTROIDS_BULLETMANAGER_HPP
