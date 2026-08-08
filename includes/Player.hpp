#pragma once

#include "Bullet.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>
#include <array>

class Player {
    // Player
    Sprite    _sprite;
    SDL_FRect _hitbox;
    float angle = 0;

    // Movement
    SDL_Point _accel{};
    float _accel_spd = 6.f;   // pixels per second
    float _deccel_spd = 0.25f; // pixels per second
    float _max_spd = 300.f;

    // Shooting
    std::array<Bullet, 1000> bullets;
    int shoot_cooldown = 30; // frames
    int shoot_timer = 0; // frames 

    void look_at(float x, float y);

    void move(float delta_time);

    void input();

    void shoot();
public:
    Player() = default;
    Player(
        Sprite sprite,
        float x, float y
    );

    void update(SDL_Renderer *renderer, float delta_time);

    void render(SDL_Renderer *renderer, bool debug);
};