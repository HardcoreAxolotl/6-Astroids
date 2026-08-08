#include "Bullet.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cmath>

void Bullet::init(Sprite &sprite) {
    _global_sprite = sprite;
}

Bullet::Bullet() {
    _sprite = _global_sprite;
    _sprite.pivot(4, 4);
    active = false;
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0;
}

// Spawn & Despawn
void Bullet::spawn(SDL_FPoint position, SDL_FPoint velocity, float angle) {
    _position = position;
    _velocity = velocity;
    _angle = angle;
    active = true;
    SDL_Log("Bullet spawned");
}

void Bullet::despawn() {
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0;
    active = false;
    SDL_Log("Bullet despawned");
}

// Move
void Bullet::move(float delta_time) {
    _position.x += _velocity.x * delta_time;
    _position.y += _velocity.y * delta_time;
    //SDL_Log("Bullet moved");
}

// Update & Rendering
void Bullet::update(float delta_time) {
    move(delta_time);
    _sprite.position(_position.x, _position.y);

    if (_position.x > 640) {
        _position.x = -32;
    }
    if (_position.x < -32) {
        _position.x = 640;
    }
    if (_position.y > 640) {
        _position.y = -32;
    }
    if (_position.y < -32) {
        _position.y = 640;
    }
    //SDL_Log("Bullet update");
}


void Bullet::render(SDL_Renderer *renderer, bool debug) {
    _sprite.render(renderer, _angle * (180.0f / M_PI));
    //SDL_Log("Bullet renderer");
}
