#include "engine.h"
#include "SDL2/SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <stdbool.h>
#include <stdio.h>

bool engine_init(Engine *engine) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Failed to initialize SDL2 error: %s\n", SDL_GetError());
    return false;
  }
  engine->sdl_initialized = true;

  engine->window = SDL_CreateWindow("Nugget", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, 680, 480, 0);

  if (!engine->window) {
    fprintf(stderr, "Failed to create SDL2 window error: %s\n", SDL_GetError());
    return false;
  }

  engine->renderer =
      SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
  if (!engine->renderer) {
    fprintf(stderr, "Failed to create SDL2 renderer error: %s\n",
            SDL_GetError());
    return false;
  }

  engine->dt = 0;
  engine->is_running = true;

  return true;
}

void engine_run(Engine *engine) {
  while (engine->is_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: {
        engine->is_running = false;
        break;
      }
      default:
        break;
      }
    }
    SDL_RenderClear(engine->renderer);
    SDL_RenderPresent(engine->renderer);
  }
}

void engine_destroy(Engine *engine) {
  if (engine->renderer)
    SDL_DestroyRenderer(engine->renderer);

  if (engine->window)
    SDL_DestroyWindow(engine->window);

  engine->is_running = false;
  engine->renderer = NULL;
  engine->window = NULL;
  engine->dt = 0;

  if (engine->sdl_initialized)
    SDL_Quit();
}
