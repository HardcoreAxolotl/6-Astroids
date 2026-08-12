//
// Created by HardcoreAxolotl on 10/08/2026.
//

#include "../includes/BulletManager.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

#include "../includes/Player.hpp"

BulletManager::BulletManager() {
    for (auto &bullet : bullets) {
        bullet.active = false;
    }
    bullet_speed = 400.0f; // pixels per second
}

void BulletManager::SpawnBullet(Player *player) {
    auto it = std::ranges::find_if(bullets, [](const Bullet& b) {
        return !b.active;
    });

    if (it != bullets.end() && !it->active) {
        it->spawn(
            SDL_FPoint(
                player->position().x+player->size().x/2+cosf(player->angle())*32,
                player->position().y+player->size().y/2+sinf(player->angle())*32),
            SDL_FPoint(cosf(player->angle()) * bullet_speed,
            sinf(player->angle()) * bullet_speed),
            player->angle()
        );
    }
}


void BulletManager::RenderBullets(SDL_Renderer *renderer, bool debug) {
    for(auto &bullet : bullets) {
        if (bullet.active) bullet.render(renderer, debug);
    }
}

void BulletManager::UpdateBullets(float delta_time) {
    for(auto &bullet : bullets) {
        if (bullet.active) bullet.update(delta_time);
    }
}
