#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "aabb.h"
#include "include/common.h"

// Define window extremities
#define WINDOW_H 480
#define WINDOW_W 640

// SDL Drawing
SDL_Window *_window;
SDL_Renderer *_renderer;
SDL_Rect _headerRect;
SDL_Texture *_headerText;

// AABB Array
aabb *aabbs[2];
aabb *_selectedAABB;
vec2 _scale = (vec2) {.x = 1.1f, .y = 1.1f};

// Whether mouse button is held down within an AABB
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

/// Handle mouse click and drag
/// \param e
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

void init_aabbs()
{
    // Couple of AABBs
    aabb *a1 = cInitAABB(
            (vec2) {
                    .x = 100,
                    .y = 100
            },
            (vec2) {
                    .x = 50,
                    .y = 50
            });

    aabb *a2 = cInitAABB(
            (vec2) {
                    .x = 250,
                    .y = 250
            },
            (vec2) {
                    .x = 50,
                    .y = 50
            });

    aabbs[0] = a1;
    aabbs[1] = a2;

    // Default selected to first aabb
    _selectedAABB = a1;
}

void init_sdl()
{
    int rc = 0;

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

    // Instructions
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 18);

    SDL_Color white = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended( font, "Select and Drag with Mouse. Square Brackets [ ] to scale", white );

    _headerText = SDL_CreateTextureFromSurface(_renderer, textSurface);

    _headerRect.x = WINDOW_W / 2 - textSurface->w / 2;
    _headerRect.y = 0;
    _headerRect.w = textSurface->w;
    _headerRect.h = textSurface->h;
}

/// Main (entry point)
/// \return 0 on any clean exit
int main()
{
    SDL_Event event;
    SDL_bool loop = SDL_TRUE;

    init_sdl();
    init_aabbs();

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
                        cAABBScale(_selectedAABB, cVec2Inverse(_scale));
                        break;
                    case SDLK_RIGHTBRACKET:
                        cAABBScale(_selectedAABB, _scale);
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
        }

        SDL_RenderCopy(_renderer, _headerText, NULL, &_headerRect);

        // Draw to renderer
        SDL_RenderPresent(_renderer);

        SDL_Delay(10);
    }

    // Destroy, quit SDL and exit
    SDL_DestroyWindow(_window);
    SDL_Quit();
    exit(0);
}