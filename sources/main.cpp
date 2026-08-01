#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

struct AppState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    AppState *state = static_cast<AppState *>(SDL_calloc(1, sizeof(AppState)));    
    if (!state) {
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("SDL3 Callback App", 640, 480, 0, &state->window, &state->renderer)) {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = (AppState *)appstate;

    // Clear screen to blue
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 255, 255);
    SDL_RenderClear(state->renderer);
    
    // Present the frame
    SDL_RenderPresent(state->renderer);

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
