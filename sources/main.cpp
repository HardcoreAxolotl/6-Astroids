#include <main.hpp>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>

#include "Astroid.hpp"
#include "AstroidManager.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "BulletManager.hpp"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    // Init SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Setup metadata
    SDL_SetAppMetadata("Astroids", "1.0", "dev.roboticaxolotl.astorids");

    // Setup state
    auto *state = new AppState();
    if (!state) {
        SDL_Log("Failed to allocate AppState");
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    // Create window & renderer
    if (!SDL_CreateWindowAndRenderer("Astroids", 640, 640, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Set the renderer size to 640x640
    SDL_SetRenderLogicalPresentation(state->renderer, 640, 640, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Load bullet texture
    SDL_Texture *bullet_tex = IMG_LoadTexture(state->renderer, "assets/sprites/bullet.png");
    auto bullet_texture = Sprite(bullet_tex);
    Bullet::init(bullet_texture);

    // Setup player
    SDL_Texture *player_tex = IMG_LoadTexture(state->renderer, "assets/sprites/player.png");
    state->player = Player(Sprite(player_tex), 320, 320);

    state->last_time = SDL_GetPerformanceCounter();
    state->frequency = SDL_GetPerformanceFrequency();

    // Astroid sprites
    SDL_Texture *big_tex = IMG_LoadTexture(state->renderer, "assets/sprites/big_astroid.png");
    SDL_Texture *small_tex = IMG_LoadTexture(state->renderer, "assets/sprites/small_astroid.png");

    state->astroid_manager = AstroidManager(
        new Sprite(big_tex),
        new Sprite(small_tex)
    );

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = (AppState *)appstate;
    auto renderer = state->renderer;
    auto player = state->player;
    auto bullet_manager = state->bullet_manager;
    auto astroid_manager = state->astroid_manager;

    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 frameElapsedTime = current_time - state->last_time;
    state->last_time = current_time;

    float delta_time = static_cast<float>(frameElapsedTime) / static_cast<float>(state->frequency);
    if (delta_time > 0.1f) delta_time = 0.1f;
    
    static float total = 0.0f;
    static int frames = 0;

    total += delta_time;
    frames++;

    // Calculate FPS and Bullet Count every 6000 frames
    if (frames == 6000)
    {
        // Change the title
        const std::string title = "Astroids | FPS: " + std::to_string(frames / total) + " | Bullets: " + std::to_string(Bullet::bullet_count) + " | Astroids: " + std::to_string(AstroidManager::astroid_count);
        SDL_SetWindowTitle(state->window, title.c_str());
        total = 0.0f;
        frames = 0;
    }

    // Update
    Update(state, delta_time);

    // Render
    Render(state, true);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *state = (AppState *)appstate;

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // Terminate the app cleanly
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState *state = (AppState *)appstate;
    if (state) {
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        SDL_free(state);
    }
    SDL_Quit();
}
