#include "Bullet.hpp"
#include "Player.hpp"
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include "Player.hpp"
#include <SDL3/SDL_mouse.h>

struct AppState {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
    Uint64 last_time = 0;
    Uint64 frequency = 0;
    Player player;
};
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    SDL_SetAppMetadata("Astroids", "1.0", "dev.roboticaxolotl.astorids");

    AppState *state = static_cast<AppState *>(SDL_calloc(1, sizeof(AppState)));    
    if (!state) {
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("Astroids", 640, 640, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(state->renderer, 640, 640, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    auto bullet_texture = Sprite(IMG_LoadTexture(state->renderer, "assets/sprites/bullet.png"));
    Bullet::init(bullet_texture);
    state->player = Player(Sprite(IMG_LoadTexture(state->renderer, "assets/sprites/player.png")), 100, 100);
    state->last_time = SDL_GetPerformanceCounter();
    state->frequency = SDL_GetPerformanceFrequency();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = (AppState *)appstate;
    auto renderer = state->renderer;

    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 frameElapsedTime = current_time - state->last_time;
    state->last_time = current_time;

    float delta_time = static_cast<float>(frameElapsedTime) / static_cast<float>(state->frequency);
    if (delta_time > 0.1f) delta_time = 0.1f;
    
    static float total = 0.0f;
    static int frames = 0;

    total += delta_time;
    frames++;

    if (frames == 300)
    {
        SDL_Log("Average FPS: %.1f", frames / total);
        total = 0.0f;
        frames = 0;
    }

    state->player.update(renderer, delta_time);

    // Clear screen to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    state->player.render(renderer, true);

    // Present the frame
    SDL_RenderPresent(renderer);

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
