/*
 * Author: Jode Andrews
 * Purpose: Example AABB
 * Language:  C
 */
#include <SDL2/SDL.h>
#include "aabb.h"
#include "include/common.h"

// Define window extremities
#define WINDOW_H 480
#define WINDOW_W 640

// SDL Drawing
SDL_Window *_window;
SDL_Renderer *_renderer;

// AABB Array
aabb *aabbs[2];

/// Transpose AABB to an SDL Rect
/// \param raabb
/// \return SDL_Rect rect
SDL_Rect SDL_RectAABB(aabb *raabb) {
    SDL_Rect r = {
            .x = (int) raabb->topLeft(raabb).x,
            .y = (int) raabb->topLeft(raabb).y,
            .w = (int) raabb->he.x * 2,
            .h = (int) raabb->he.y * 2
    };

    return r;
}

/// Main (entry point)
/// \return 0 on any clean exit
int main() {
    int rc = 0;
    SDL_Event event;
    SDL_bool loop = SDL_TRUE;

    // Only need video
    rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc != 0) {
        printf("[Error] Initialising SDL");
        exit(0);
    }

    // Shortcut create an SDL window and renderer
    rc = SDL_CreateWindowAndRenderer(WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN, &_window, &_renderer);
    if (rc != 0) {
        printf("[Error] Creating Window and Renderer");
        exit(0);
    }

    // Couple of AABBs
    aabb *a1 = cInitAABB(
            (vec2) {
                    .x = 0,
                    .y = 0
            },
            (vec2) {
                    .x = 50,
                    .y = 50
            });

    aabb *a2 = cInitAABB(
            (vec2) {
                    .x = 70,
                    .y = 70
            },
            (vec2) {
                    .x = 50,
                    .y = 50
            });

    aabbs[0] = a1;
    aabbs[1] = a2;

    while (loop) {
        // Handle SDL Events
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            loop = SDL_FALSE;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    loop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }

        // Physics

        enum cBOOL c = cAABBOverlap(aabbs[0], aabbs[1]);

        // Draw

        // Blank Window as black
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);

        // Draw AABB rectangles as white
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 1);

        // Iterate over AABBs array and draw as SDL Rects
        for (int i = 0; i < (sizeof(aabbs)/ sizeof(aabbs[0])); i++) {
            SDL_Rect r = SDL_RectAABB(aabbs[i]);
            SDL_RenderDrawRect(_renderer, &r);
        }

        // Draw to renderer
        SDL_RenderPresent(_renderer);
    }

    // Destroy, quit SDL and exit
    SDL_DestroyWindow(_window);
    SDL_Quit();
    exit(0);
}