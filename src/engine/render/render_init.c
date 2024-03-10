//
// Created by Shivam Acharya on 02/02/2024.
//
#include "../state.h"
#include "../util.h"
#include "render.h"

void init_render_state(RenderState *render_state)
{
  ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize: %s\n",
         SDL_GetError());

  render_state->window = SDL_CreateWindow(
      "CEngine", SDL_WINDOWPOS_CENTERED_DISPLAY(0),
      SDL_WINDOWPOS_CENTERED_DISPLAY(0), 1080, 1080, SDL_WINDOW_ALLOW_HIGHDPI);

  ASSERT(render_state->window, "failed to create SDL window: %s\n",
         SDL_GetError());

  render_state->renderer =
      SDL_CreateRenderer(render_state->window, -1, SDL_RENDERER_PRESENTVSYNC);

  render_state->texture = SDL_CreateTexture(
      render_state->renderer, SDL_PIXELFORMAT_ABGR8888,
      SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

  ASSERT(render_state->texture, "failed to create SDL texture: %s\n",
         SDL_GetError());

  render_state->pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
  ASSERT(render_state->pixels, "failed to allocate pixels");

  render_state->params.pos = (v2){5, 5};
  render_state->params.dir = ((v2){-1.0f, 0.0f});
  render_state->params.plane = (v2){0.0f, 1.0f};
}

void free_render_state(RenderState *state) { free(state->pixels); }
