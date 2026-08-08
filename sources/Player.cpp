#include "Player.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3_gfx/SDL3_gfxPrimitives.h>
#include <algorithm>
#include <cmath>

void Player::look_at(float x, float y) {
    float delta_x = x - _hitbox.x;
    float delta_y = y - _hitbox.y;

    // Convert relative vectors to an absolute tracking angle
    angle = std::atan2(delta_y, delta_x);
}

void Player::shoot() {
    auto it = std::find_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return !b.active; 
    });

    if (it != bullets.end() && !it->active) {
        float bullet_speed = 400.0f; // 400 pixels per second

        it->spawn(
            SDL_FPoint(_hitbox.x + _hitbox.w / 2.0f + cosf(angle) * 32.0f, 
            _hitbox.y + _hitbox.h / 2.0f + sinf(angle) * 32.0f),
            SDL_FPoint(cosf(angle) * bullet_speed, 
            sinf(angle) * bullet_speed),
            angle
        );
    }
}


void Player::move(float delta_time) {
    _hitbox.x += _accel.x * delta_time;
    _hitbox.y += _accel.y * delta_time;

    if (_hitbox.x > 640+32) {
        _hitbox.x = -32;
    }
    if (_hitbox.x < -32) {
        _hitbox.x = 640+32;
    }
    if (_hitbox.y > 640+32) {
        _hitbox.y = -32;
    }
    if (_hitbox.y < -32) {
        _hitbox.y = 640+32;
    }

    _accel.x -= std::copysign(_deccel_spd, _accel.x);
    _accel.y -= std::copysign(_deccel_spd, _accel.y);
}

void Player::input() {
    const bool* keys = SDL_GetKeyboardState(nullptr); 

    if (keys[SDL_SCANCODE_W]) _accel.y += -_accel_spd; // Move Up
    if (keys[SDL_SCANCODE_S]) _accel.y += _accel_spd;  // Move Down
    if (keys[SDL_SCANCODE_A]) _accel.x += -_accel_spd; // Move Left
    if (keys[SDL_SCANCODE_D]) _accel.x += _accel_spd;  // Move Right

    _accel.x = std::clamp<float>(_accel.x, -_max_spd, _max_spd);
    _accel.y = std::clamp<float>(_accel.y, -_max_spd, _max_spd);
}
Player::Player(
    Sprite sprite,
    float x, float y
) 
: _sprite(std::move(sprite)), _hitbox({x-8, y-8, 16,16}) {
    _sprite.position(100, 100);
    _sprite.pivot(32, 30);
}

void Player::update(SDL_Renderer *renderer, float delta_time) {
    float mx, my;
    auto m_state = SDL_GetMouseState(&mx, &my);
    SDL_RenderCoordinatesFromWindow(renderer, mx, my, &mx, &my);

    look_at(mx, my);

    if (shoot_timer > 0) shoot_timer--;
    if ((m_state & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) && (shoot_timer <= 0)) {
        shoot();
        shoot_timer = shoot_cooldown;
    }

    // Move Player
    input();
    move(delta_time);
    _sprite.position(_hitbox.x + _hitbox.w / 2, _hitbox.y + _hitbox.h / 2);

    // Update Bullets
    for(auto &bullet : bullets) {
        if (bullet.active) bullet.update(delta_time);
    }
}


void Player::render(SDL_Renderer *renderer, bool debug) {
    for(auto &bullet : bullets) {
        if (bullet.active) bullet.render(renderer, debug);
    }

    if (debug) {
        // Hitbox Display
        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        
        // Hurtbox Display
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &_hitbox);

        circleRGBA(renderer, _hitbox.x+_hitbox.w/2, _hitbox.y+_hitbox.h/2, 32, 255, 0, 255, 255);

        filledCircleRGBA(
            renderer, 
            _hitbox.x+_hitbox.w/2+cosf(angle)*32, 
            _hitbox.y+_hitbox.h/2+sinf(angle)*32, 
            4, 
            255, 0, 255, 255
        );
    }
    _sprite.render(renderer, angle * (180.0f / M_PI)); // need to multiplie by (180.0f / M_PI) for some reason
}
