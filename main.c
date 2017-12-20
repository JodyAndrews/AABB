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
aabb *_selectedAABB;
enum cBOOL inAABB = cFALSE;

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

void handleMouseDrag(SDL_Event e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int i = 0;
        do {
            if (aabbs[i]->containsPoint(aabbs[i], (vec2) {.x = e.motion.x, .y = e.motion.y})) {
                _selectedAABB = aabbs[i];
                inAABB = cTRUE;
                break;
            }
            i++;
        } while (i < sizeof(aabbs) / sizeof(aabbs[0]));
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        inAABB = cFALSE;
    }

    if (e.type == SDL_MOUSEMOTION) {
        if (inAABB) {
            _selectedAABB->center.x += e.motion.xrel;
            _selectedAABB->center.y += e.motion.yrel;
        }
    }
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
    vec2 v = (vec2) {.x = 1.1f, .y = 1.1f};

    _selectedAABB = a1;

    while (loop) {
        // Handle SDL Events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loop = SDL_FALSE;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = SDL_FALSE;
                        break;
                    case SDLK_LEFTBRACKET:
                        cAABBScale(_selectedAABB, cVec2Inverse(v));
                        break;
                    case SDLK_RIGHTBRACKET:
                        cAABBScale(_selectedAABB, v);
                        break;
                    default:
                        break;
                }
            }
            handleMouseDrag(event);
        }

        // Blank Window as black
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);

        // Draw AABB rectangles as white
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 1);

        vec2 intersection = cVec2Zero();

        // Draw AABB rectangles yellow if overlapping
        if (cAABBOverlap(aabbs[0], aabbs[1], &intersection)) {
            SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 1);
        }

        // Iterate over AABBs array and draw as SDL Rects
        for (int i = 0; i < (sizeof(aabbs) / sizeof(aabbs[0])); i++) {
            SDL_Rect r = SDL_RectAABB(aabbs[i]);
            if (_selectedAABB == aabbs[i]) {
                SDL_RenderFillRect(_renderer, &r);
            } else {
                SDL_RenderDrawRect(_renderer, &r);
            }
            /*printf("The value of s is: %p\n", (void *) _selectedAABB);
            printf("The direction of s is: %p\n", (void *) &_selectedAABB);
            SDL_Rect r = SDL_RectAABB(aabbs[i]);
            SDL_RenderDrawRect(_renderer, &r);*/
        }

        // Draw to renderer
        SDL_RenderPresent(_renderer);
    }

    // Destroy, quit SDL and exit
    SDL_DestroyWindow(_window);
    SDL_Quit();
    exit(0);
}