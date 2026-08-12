#include "Astroid.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cmath>
#include <SDL3_gfx/SDL3_gfxPrimitives.h>

#include "AstroidManager.hpp"
#include "util.hpp"

// Base virtual method implementations (required for vtable and linking)

void Astroid::spawn(size_t index, SDL_FPoint position, SDL_FPoint direction, float angle) {
    if (!_sprite) _sprite.pivot(4, 4);
    _position = position;
    _velocity = {direction.x * _speed, direction.y * _speed};
    _angle = angle;
    _index = index;
    AstroidManager::astroid_count++;
}

Astroid::Astroid(float radius, float speed) : _radius(radius), _speed(speed) {
    if (!_sprite) {
        _sprite.pivot(4, 4);
    }
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0.0f;
    SDL_Log("Astroid ctor: %p radius=%.2f speed=%.2f", (void*)this, _radius, _speed);
}

// Despawn
void Astroid::despawn() {
    _position = {-16.f, -16.f};
    _velocity = {0.f, 0.f};
    _angle = 0.0f;
    AstroidManager::astroid_count--;
    AstroidManager::clean_up(_index);
    //SDL_Log("Astroid despawned");
}

// Damage
void Astroid::damage(float damage) {
    _health -= damage;
    if (_health <= 0) {
        despawn();
    }
}

// Move
void Astroid::move(float delta_time) {
    _position.x += _velocity.x * delta_time;
    _position.y += _velocity.y * delta_time;
    //SDL_Log("Astroid moved");
}

// Update & Rendering
void Astroid::update(float delta_time) {
    move(delta_time);
    _sprite.position(_position.x, _position.y);

    if (_position.x > 640+_radius) {
        _position.x = -32-_radius;
    }
    if (_position.x < -32-_radius) {
        _position.x = 640+_radius;
    }
    if (_position.y > 640+_radius) {
        _position.y = -32-_radius;
    }
    if (_position.y < -32-_radius) {
        _position.y = 640+_radius;
    }
    //SDL_Log("Astroid update");
}


void Astroid::render(SDL_Renderer *renderer, bool debug) {
    _sprite.render(renderer, _angle * (180.0f / M_PI));
    _angle += 0.00001 * _speed/100;
    if (debug) {
        circleColor(renderer, _position.x, _position.y, _radius, 0xFF0000FF);
    }
    //SDL_Log("Astroid renderer");
}
