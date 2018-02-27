#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "aabb.h"


// Define window extremities
#define WINDOW_H 480
#define WINDOW_W 640

// SDL Drawing
SDL_Window *_window;
SDL_Renderer *_renderer;
// Where we're drawing our header to
SDL_Rect _headerTextRect;
// Our header texture
SDL_Texture *_headerText;

// Common Font
TTF_Font *font;

// AABB Array
aabb *aabbs[2];
aabb *_selectedAABB;
aabb *_intersectingAABB;

vec2 _scale = (vec2) {.x = 1.1f, .y = 1.1f};

SDL_Color white = {255, 255, 255};

// Whether mouse button is held down within an AABB
bool inAABB = false;

/// Transpose AABB to an SDL Rect
/// \param raabb
/// \return SDL_Rect rect
SDL_Rect SDL_RectAABB(aabb *raabb)
{
  SDL_Rect r = {
          .x = (int) mAABBTopLeft(raabb).x,
          .y = (int) mAABBTopLeft(raabb).y,
          .w = (int) ceil(raabb->he.x * 2),
          .h = (int) ceil(raabb->he.y * 2)
  };

  return r;
}

/// Handle mouse click and drag
/// \param e
void handleMouseDrag(SDL_Event e)
{
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int i = 0;
    do {
      if (mAABBContainsPoint(aabbs[i], (vec2) {.x = e.motion.x, .y = e.motion.y})) {
        _selectedAABB = aabbs[i];
        inAABB = true;
        break;
      }
      i++;
    } while (i < sizeof(aabbs) / sizeof(aabbs[0]));
  }

  if (e.type == SDL_MOUSEBUTTONUP) {
    inAABB = false;
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
  aabb *a1 = mInitAABB(
          (vec2) {
                  .x = 100,
                  .y = 100
          },
          (vec2) {
                  .x = 50,
                  .y = 50
          });

  aabb *a2 = mInitAABB(
          (vec2) {
                  .x = 200,
                  .y = 200
          },
          (vec2) {
                  .x = 50,
                  .y = 50
          });

  aabbs[0] = a1;
  aabbs[1] = a2;

  // AABB to store the intersection depth
  _intersectingAABB = mInitAABB(
          (vec2) {
                  .x = 0,
                  .y = 0
          },
          (vec2) {
                  .x = 0,
                  .y = 0
          }
  );

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
  font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 18);


  SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Select and Drag with Mouse. Scale [ ]. Stretch WASD",
                                                    white);

  _headerText = SDL_CreateTextureFromSurface(_renderer, textSurface);

  _headerTextRect.x = WINDOW_W / 2 - textSurface->w / 2;
  _headerTextRect.y = 0;
  _headerTextRect.w = textSurface->w;
  _headerTextRect.h = textSurface->h;

  SDL_FreeSurface(textSurface);
  textSurface = NULL;
}

/// Main (entry point)
/// \return 0 on any clean exit
int main()
{
  SDL_Event event;
  SDL_bool loop = SDL_TRUE;

  bool intersecting = false;
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
            mAABBScale(_selectedAABB, mVec2Inv(_scale));
            break;
          case SDLK_RIGHTBRACKET:
            mAABBScale(_selectedAABB, _scale);
            break;
          case SDLK_w:
            mAABBStretch(_selectedAABB, (vec2) {.x = 0, .y = -2});
            break;
          case SDLK_d:
            mAABBStretch(_selectedAABB, (vec2) {.x = 2, .y = 0});
            break;
          case SDLK_s:
            mAABBStretch(_selectedAABB, (vec2) {.x = 0, .y = 2});
            break;
          case SDLK_a:
            mAABBStretch(_selectedAABB, (vec2) {.x = -2, .y = 0});
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

    // Signed depth of intersection point
    vec2 intersection = VEC2ZERO;
    intersecting = mAABBOverlap(aabbs[0], aabbs[1], &intersection);

    // Draw AABB rectangles yellow if overlapping and get an AABB for the intersection depth
    if (intersecting) {
      SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 1);

      mAABBIntersection(aabbs[0], aabbs[1], _intersectingAABB);
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

    // Iterate over AABBs array and draw center points
    for (int i = 0; i < (sizeof(aabbs) / sizeof(aabbs[0])); i++) {
      SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 1);
      SDL_RenderDrawPoint(_renderer, (int) aabbs[i]->center.x, (int) aabbs[i]->center.y);
    }

    // If intersecting then draw the AABB to show the intersection depth
    if (intersecting) {
      SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 1);
      SDL_Rect r = SDL_RectAABB(_intersectingAABB);
      SDL_RenderFillRect(_renderer, &r);
      SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 1);
      SDL_RenderDrawPoint(_renderer, (int)_intersectingAABB->center.x, (int)_intersectingAABB->center.y);
    }

    SDL_RenderCopy(_renderer, _headerText, NULL, &_headerTextRect);

    // Draw to renderer
    SDL_RenderPresent(_renderer);

    SDL_Delay(10);
  }

  // Destroy, quit SDL and exit
  SDL_DestroyTexture(_headerText);
  SDL_DestroyWindow(_window);
  SDL_Quit();
  exit(0);
}