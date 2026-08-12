#include "Bullet.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cmath>

#include "Astroid.hpp"
#include "AstroidManager.hpp"
#include "util.hpp"

void Bullet::init(Sprite &sprite) {
    SDL_Log("Bullet::init called with sprite tex=%p", sprite.texture());
    _global_sprite = sprite;
    _global_sprite.pivot(4, 4);
    SDL_Log("Bullet global sprite initialized: tex=%p", _global_sprite.texture());
}

Bullet::Bullet() {
    SDL_Log("Bullet ctor: %p global_tex=%p", (void*)this, _global_sprite.texture());
    if (!_sprite) {
        _sprite = _global_sprite;
        _sprite.pivot(4, 4);
    }
    active = false;
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0.0f;
}

// Spawn & Despawn
void Bullet::spawn(SDL_FPoint position, SDL_FPoint velocity, float angle) {
    if (!_sprite) _sprite = _global_sprite;
    _position = position;
    _velocity = velocity;
    _angle = angle;
    active = true;
    health = 1;
    bullet_count++;
    //SDL_Log("Bullet spawned");
}

void Bullet::despawn() {
    if (!active) return;
    active = false;
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0.0f;
    bullet_count--;
    //SDL_Log("Bullet despawned");
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
        health--;
    }
    if (_position.x < -32) {
        _position.x = 640;
        health--;
    }
    if (_position.y > 640) {
        _position.y = -32;
        health--;
    }
    if (_position.y < -32) {
        _position.y = 640;
        health--;
    }

    for (auto astroid : AstroidManager::astroids) {
        if (astroid) {
            if (CircleRect(astroid->position().x, astroid->position().y, astroid->radius(), _position.x - 4, _position.y - 4, 8, 8)) {
                health = 0;
                astroid->damage(1);
            }
        }
    }

    if (health == 0) {
        despawn();
    }
    //SDL_Log("Bullet update");
}


void Bullet::render(SDL_Renderer *renderer, bool debug) {
    _sprite.render(renderer, _angle * (180.0f / M_PI));
    if (debug) {
        SDL_FRect hitbox = {_position.x - 4, _position.y - 4, 8, 8};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &hitbox);
    }
    //SDL_Log("Bullet renderer");
}
