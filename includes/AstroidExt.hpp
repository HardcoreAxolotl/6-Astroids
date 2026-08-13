//
// Created by HardcoreAxolotl on 12/08/2026.
//

#ifndef ASTROIDS_ASTROIDEXT_HPP
#define ASTROIDS_ASTROIDEXT_HPP
#include "Astroid.hpp"
#include "AstroidManager.hpp"
#include <SDL3/SDL_log.h>

#include "util.hpp"

struct BigAstroid : Astroid
{
    BigAstroid(float radius = 81.f, float min_speed = 50.f, float max_speed = 150.f) : Astroid(radius, randfloat(min_speed, max_speed)) {}
    void spawn(size_t index, SDL_FPoint position, SDL_FPoint direction, float angle) override {
        if (!_sprite) _sprite = AstroidManager::big_astroid;
        _position = position;
        _velocity = {direction.x * _speed, direction.y * _speed};
        _angle = angle;
        AstroidManager::astroid_count++;
        _health = randint(50, 100);
        _index = index;
        SDL_Log("BigAstroid spawned: this=%p sprite_tex=%p radius=%.1f speed=%.1f", (void*)this, _sprite.texture(), _radius, _speed);
    }
};

struct SmallAstroid : Astroid
{
    SmallAstroid(float radius = 38.f, float min_speed = 100.f, float max_speed = 250.f) : Astroid(radius, randfloat(min_speed, max_speed)) {}
    void spawn(size_t index, SDL_FPoint position, SDL_FPoint direction, float angle) override {
        if (!_sprite) _sprite = AstroidManager::small_astroid;
        _position = position;
        _velocity = {direction.x * _speed, direction.y * _speed};
        _angle = angle;
        AstroidManager::astroid_count++;
        _health = randint(10, 25);
        _index = index;
        SDL_Log("SmallAstroid spawned: this=%p sprite_tex=%p radius=%.1f speed=%.1f", (void*)this, _sprite.texture(), _radius, _speed);
    }
};
#endif //ASTROIDS_ASTROIDEXT_HPP
