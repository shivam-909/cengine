//
// Created by Shivam Acharya on 02/02/2024.
//

#ifndef RENDER_H
#define RENDER_H

#include "SDL.h"
#include <stdbool.h>

#include "../math/linmath.h"
#include "../types.h"

#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440
#define EPSILON 1e-20f
#define LARGE_VALUE 1e30f

// Parameters for the rendering engine.
typedef struct params
{
  v2 pos, dir, plane;
} RenderParams;

// The state of the rendering engine.
typedef struct render_state
{
  SDL_Window *window;
  SDL_Texture *texture;
  SDL_Renderer *renderer;

  RenderParams params;
  u32 *pixels;
} RenderState;

// Render ingests the current rendering parameters and mutates the global
// rendering state. It is called every frame.
void render(RenderState *render_state);

// Initialises the rendering state window, renderer and texture.
void init_render_state(RenderState *render_state);

// Frees the pixels. Window, Texture and Renderer should be freed using SDL
// destructors.
void free_render_state(RenderState *state);

#endif // RENDER_H
