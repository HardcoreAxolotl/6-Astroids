//
// Created by HardcoreAxolotl on 10/08/2026.
//

#include <algorithm>
#include <cmath>
#include <vector>
#include <random>

#include "Player.hpp"
#include "AstroidManager.hpp"
#include "AstroidExt.hpp"
#include "util.hpp"

Sprite AstroidManager::big_astroid;
Sprite AstroidManager::small_astroid;

void AstroidManager::clean_up(size_t index) {
    if (index < astroids.size()) {
        delete astroids[index];
        astroids[index] = nullptr;
    }
}

AstroidManager::AstroidManager(Sprite *big_astroid, Sprite *small_astroid) {
    SDL_Log("AstroidManager ctor start");
    AstroidManager::big_astroid = *big_astroid;
    AstroidManager::small_astroid = *small_astroid;
    AstroidManager::big_astroid.pivot(82, 86);
    AstroidManager::small_astroid.pivot(38, 38);
    SDL_Log("AstroidManager ctor done: big_tex=%p small_tex=%p", AstroidManager::big_astroid.texture(), AstroidManager::small_astroid.texture());
}

void AstroidManager::SpawnBigAstroid(Player *player) {
    auto it = std::ranges::find_if(astroids, [](const Astroid* a) {
        return !a;
    });

    if (it != astroids.end() && (!*it)) {
        // use a prototype to get radius/speed without dereferencing a null pointer
        BigAstroid proto;
        float r = proto.radius();
        float x;
        float y;

        if (randbool()) { // +y
            x = randfloat(0.f - r, 640 + r);
            y = 0 - r;
        }
        else if (randbool()) { // -y
            x = randfloat(0.f - r, 640 + r);
            y = 640 + r;
        }
        else if (randbool()) { // +x
            x = 640 + r;
            y = randfloat(0.f - r, 640 + r);
        }
        else { // -x
            x = 0 - r;
            y = randfloat(0.f - r, 640 + r);
        }

        float dx = player->position().x - x;
        float dy = player->position().y - y;

        float length = std::sqrt(dx * dx + dy * dy);
        if (length == 0.f) length = 1.0f; // guard against divide-by-zero

        float vx = dx / length;
        float vy = dy / length;

        std::size_t index = std::distance(astroids.begin(), it);
        *it = new BigAstroid();
        (*it)->spawn(
            index,
            SDL_FPoint{x, y},
            SDL_FPoint{vx, vy},
            0
        );
        SDL_Log("Spawned Big Astroid");
    }
}

void AstroidManager::SpawnSmallAstroid(Player *player) {
    auto it = std::ranges::find_if(astroids, [](const Astroid* a) {
        return !a;
    });

    if (it != astroids.end() && (!*it)) {
        // use a prototype to get radius/speed without dereferencing a null pointer
        SmallAstroid proto;
        float r = proto.radius();
        float x;
        float y;

        if (randbool()) { // +y
            x = randfloat(0.f - r, 640 + r);
            y = 0 - r;
        }
        else if (randbool()) { // -y
            x = randfloat(0.f - r, 640 + r);
            y = 640 + r;
        }
        else if (randbool()) { // +x
            x = 640 + r;
            y = randfloat(0.f - r, 640 + r);
        }
        else { // -x
            x = 0 - r;
            y = randfloat(0.f - r, 640 + r);
        }

        float dx = player->position().x - x;
        float dy = player->position().y - y;

        float length = std::sqrt(dx * dx + dy * dy);
        if (length == 0.f) length = 1.0f;

        float vx = dx / length;
        float vy = dy / length;

        std::size_t index = std::distance(astroids.begin(), it);
        *it = new SmallAstroid();
        (*it)->spawn(
            index,
            SDL_FPoint{x, y},
            SDL_FPoint{vx, vy},
            0
        );
        SDL_Log("Spawned Small Astroid");
    }
}


void AstroidManager::RenderAstroids(SDL_Renderer *renderer, bool debug) {
    for(auto &astroid : astroids) {
        if (astroid) astroid->render(renderer, debug);
    }
}

void AstroidManager::UpdateAstroids(float delta_time) {
    for(auto &astroid : astroids) {
        if (astroid) astroid->update(delta_time);
    }
}
