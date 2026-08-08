#pragma once
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Sprite {
    // Delcare the variables
    SDL_Texture *_tex{nullptr};
    SDL_FRect   _rect{0.0f, 0.0f, 0.0f, 0.0f};
    SDL_FPoint  _pivot{0.0f, 0.0f};
public:
    Sprite() = default;
    Sprite(SDL_Texture *texture) : _tex(texture)
    {
        // Check if texture exist
        if (!_tex) {
            // fail safe
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sprite::Sprite: Invalid texture pointer! SDL Error: %s", SDL_GetError());
            return; 
        }
        
        // get the texture width and height
        SDL_GetTextureSize(_tex, &_rect.w, &_rect.h);
    }

    // set position
    void position(float x, float y) {
        _rect.x = x;
        _rect.y = y;
    }

    // set pivot
    void pivot(float x, float y) {
        _pivot.x = x;
        _pivot.y = y;
    }

    // render the texture
    void render(SDL_Renderer *renderer, float angle = 0) {
        // make sure the texture exist to not crash the program
        if (!_tex) {
            return; 
        }

        // create a rect that has the pivot
        SDL_FRect dis_rect = {
            _rect.x - _pivot.x,
            _rect.y - _pivot.y,

            _rect.w,
            _rect.h
        };

        // draw texture
        SDL_RenderTextureRotated(
            renderer, 
            _tex, 
            NULL, 
            &dis_rect, 
            angle, 
            &_pivot, 
            SDL_FLIP_NONE);
    }
};

