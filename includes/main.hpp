//
// Created by HardcoreAxolotl on 12/08/2026.
//

#ifndef ASTROIDS_MAIN_HPP
#define ASTROIDS_MAIN_HPP
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_log.h>

#include "util.hpp"
#include "AstroidManager.hpp"
#include "BulletManager.hpp"
#include "Player.hpp"



struct AppState {
    SDL_Window *window;
    SDL_Renderer *renderer;

    Uint64 last_time = 0;
    Uint64 frequency = 0;
    Player player;
    AstroidManager astroid_manager;
    BulletManager bullet_manager;
};

inline static int spawn_cooldown = 0;
inline static int spawn_counter = 0;

inline void Update(AppState *state, float delta_time) {
    if (spawn_cooldown < spawn_counter) {
        spawn_cooldown = randint(12000, 120000); // frames
        spawn_counter = 0;
        if (randbool()) {
            state->astroid_manager.SpawnBigAstroid(&state->player);
        } else {
            state->astroid_manager.SpawnSmallAstroid(&state->player);
        }
    }
    else {
        spawn_counter++;
    }


    state->player.update(state->renderer, delta_time);

    if (state->player.is_shooting()) {
        state->bullet_manager.SpawnBullet(&state->player);
    }

    if (Bullet::bullet_count > 0) {
        state->bullet_manager.UpdateBullets(delta_time);
    }

    if (AstroidManager::astroid_count > 0) {
        state->astroid_manager.UpdateAstroids(delta_time);
    }
}

inline void Render(AppState *state, bool debug) {
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);

    state->player.render(state->renderer, debug);
    if (Bullet::bullet_count > 0) {
        state->bullet_manager.RenderBullets(state->renderer, debug);
    }

    if (AstroidManager::astroid_count > 0) {
        state->astroid_manager.RenderAstroids(state->renderer, debug);
    }

    SDL_RenderPresent(state->renderer);
}

#endif //ASTROIDS_MAIN_HPP
