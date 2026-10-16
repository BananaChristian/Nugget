#ifndef ENGINE_H
#define ENGINE_H

#include "SDL_render.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool sdl_initialized;
  bool is_running;
  float dt; // Just keep track of the delta time
} Engine;

bool engine_init(Engine *engine);
void engine_run(Engine *engine);
void engine_destroy(Engine *engine);

#endif // !ENGINE_H
