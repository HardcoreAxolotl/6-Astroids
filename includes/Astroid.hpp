#pragma once

#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>

#include "AstroidManager.hpp"

struct Astroid {
protected:
    Sprite      _sprite;
    SDL_FPoint  _position;
    SDL_FPoint  _velocity;
    float       _angle;
    float       _radius;
    float       _speed; // pixels per secod
    int         _health;
    size_t      _index;

    void move(float delta_time);
public:
    virtual ~Astroid() = default;

    Astroid(float radius, float speed);

    [[nodiscard]]
    float radius() const {
        return _radius;
    };

    [[nodiscard]]
    SDL_FPoint position() const {
        return _position;
    }

    virtual void spawn(size_t index, SDL_FPoint position, SDL_FPoint direction, float angle);
    void despawn();
    void damage(float damage);

    void update(float delta_time);
    void render(SDL_Renderer *renderer, bool debug);
};
