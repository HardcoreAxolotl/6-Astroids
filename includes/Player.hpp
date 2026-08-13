#pragma once

#include "Bullet.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>
#include <array>

class Player {
    // Player
    Sprite    _sprite;
    SDL_FRect _hitbox;
    float _angle = 0;

    // Movement
    SDL_Point _accel{};
    float _accel_spd = 6.f;   // pixels per second
    float _deccel_spd = 0.25f; // pixels per second
    float _max_spd = 300.f;

    // Shooting
    float shoot_cooldown = 0.05f; // seconds
    float shoot_timer = 0.f; // seconds
    bool shooting = false;

    void look_at(float x, float y);

    void move(float delta_time);

    void input();
public:
    Player() = default;
    Player(
        Sprite sprite,
        float x, float y
    );

    bool is_shooting() const {
        return shooting;
    }

    SDL_FPoint position() const {
        return {_hitbox.x, _hitbox.y};
    }
    SDL_FPoint size() {
        return {_hitbox.w, _hitbox.h};
    }
    float angle() {
        return _angle;
    }

    void update(SDL_Renderer *renderer, float delta_time);

    void render(SDL_Renderer *renderer, bool debug);
};