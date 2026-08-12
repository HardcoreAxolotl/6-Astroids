#pragma once

#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>

class Bullet {
    friend class BulletManager;
    inline static Sprite _global_sprite;
    Sprite      _sprite;
    SDL_FPoint  _position{};
    SDL_FPoint  _velocity{};
    float       _angle;

    int health{};

    void move(float delta_time);
public:
    inline static size_t bullet_count = 0;
    bool active;

    Bullet();
    static void init(Sprite &sprite);

    void spawn(SDL_FPoint position, SDL_FPoint velocity, float angle);
    void despawn();

    void update(float delta_time);
    void render(SDL_Renderer *renderer, bool debug);
};
