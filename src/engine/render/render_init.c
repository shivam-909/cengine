//
// Created by Shivam Acharya on 02/02/2024.
//
#include "../global.h"
#include "../util.h"
#include "render.h"

void init_render_state()
{
  ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize: %s\n",
         SDL_GetError());

  global.render_state.window = SDL_CreateWindow(
      "CEngine", SDL_WINDOWPOS_CENTERED_DISPLAY(0),
      SDL_WINDOWPOS_CENTERED_DISPLAY(0), 1280, 720, SDL_WINDOW_ALLOW_HIGHDPI);

  ASSERT(global.render_state.window, "failed to create SDL window: %s\n",
         SDL_GetError());

  global.render_state.renderer = SDL_CreateRenderer(
      global.render_state.window, -1, SDL_RENDERER_PRESENTVSYNC);

  global.render_state.texture = SDL_CreateTexture(
      global.render_state.renderer, SDL_PIXELFORMAT_ABGR8888,
      SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

  ASSERT(global.render_state.texture, "failed to create SDL texture: %s\n",
         SDL_GetError());

  global.render_state.pixels =
      malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
  ASSERT(global.render_state.pixels, "failed to allocate pixels");

  global.render_state.params.pos = (v2){2, 2};
  global.render_state.params.dir = normalize(((v2){-1.0f, 0.1f}));
  global.render_state.params.plane = (v2){0.0f, 0.66f};
}

void free_render_state(RenderState *state) { free(global.render_state.pixels); }
